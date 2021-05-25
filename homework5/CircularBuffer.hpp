#include <exception>

template<typename T>
//fixed without inheritance from std::iterator
class CircularBufferIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::ptrdiff_t;
    using difference_type = T;
    using pointer = value_type *;
    using reference = value_type &;

    T *currentPosition;
    T *positionOfLastElement;
    T *positionOfFirstElement;

    CircularBufferIterator(T *currentPosition, T *positionOfFirstElement, T *positionOfLastElement) {
        this->currentPosition = currentPosition;
        this->positionOfFirstElement = positionOfFirstElement;
        this->positionOfLastElement = positionOfLastElement;
    }

    ~CircularBufferIterator() = default;

    T &operator*() {
        return *this->currentPosition;
    };

    T *operator->() {
        return this->currentPosition;
    }

    CircularBufferIterator &operator++() {
        this->currentPosition++;
        if (this->currentPosition > this->positionOfLastElement) {
            this->currentPosition = this->positionOfFirstElement;
        }
        return *this;
    }

    CircularBufferIterator &operator--() {
        this->currentPosition--;
        if (this->currentPosition < this->positionOfFirstElement) {
            this->currentPosition = this->positionOfLastElement;
        }
        return *this;
    }

    CircularBufferIterator operator-(difference_type iter) {
        if (this->currentPosition - iter < this->positionOfFirstElement) {
            auto temp = iter - std::distance(this->currentPosition, this->positionOfFirstElement);
            return CircularBufferIterator(this->positionOfLastElement - temp + 1,
                                          this->positionOfFirstElement,
                                          this->positionOfLastElement);
        } else {
            return CircularBufferIterator(this->currentPosition - iter, this->positionOfFirstElement,
                                          this->positionOfLastElement);
        }
    }

    difference_type operator-(CircularBufferIterator<T> &iter) {
        if (this->currentPosition < iter.currentPosition) {
            return std::distance(iter.currentPosition, iter.positionOfLastElement) +
                   std::distance(this->positionOfFirstElement, this->currentPosition) + 1;
        } else {
            return this->currentPosition - iter.currentPosition;
        }
    }

    CircularBufferIterator operator+(difference_type iter) {
        if (this->currentPosition + iter > this->positionOfLastElement) {
            auto temp = iter - std::distance(this->currentPosition, this->positionOfLastElement);
            return CircularBufferIterator(this->positionOfFirstElement + temp - 1,
                                          this->positionOfFirstElement,
                                          this->positionOfLastElement);
        } else {
            return CircularBufferIterator(this->currentPosition + iter, this->positionOfFirstElement,
                                          this->positionOfLastElement);
        }
    }

    CircularBufferIterator &operator+=(difference_type iter) {
        this->currentPosition += iter;
        if (this->currentPosition > this->positionOfLastElement) {
            this->currentPosition =
                    this->positionOfFirstElement + std::distance( this->positionOfLastElement, this->currentPosition) -
                    1;
        }
        return *this;
    }

    CircularBufferIterator &operator-=(difference_type iter) {
        this->currentPosition -= iter;
        if (this->currentPosition < this->positionOfFirstElement) {
            this->currentPosition =
                    this->positionOfLastElement - std::distance(this->currentPosition, this->positionOfFirstElement) +
                    1;
        }
        return *this;
    }

    CircularBufferIterator &operator=(const CircularBufferIterator &iter) {
        this->currentPosition = iter.currentPosition;
        return *this;
    }

    CircularBufferIterator &operator=(T *iter) {
        this->currentPosition = iter;
        return *this;
    }

    bool operator==(const CircularBufferIterator &a) const {
        return this->currentPosition == a.currentPosition;
    }

    bool operator!=(const CircularBufferIterator &a) const {
        return this->currentPosition != a.currentPosition;
    }

    bool operator<(T *pointer) {
        return this->currentPosition < pointer;
    }

    bool operator<(const CircularBufferIterator &a) {
        return this->currentPosition < a.currentPosition;
    }

    bool operator>(T *pointer) {
        return this->currentPosition > pointer;
    }

    bool operator>(const CircularBufferIterator &a) {
        return this->currentPosition > a.currentPosition;
    }

    bool operator<=(T *pointer) {
        return this->currentPosition <= pointer;
    }

    bool operator<=(const CircularBufferIterator &a) {
        return this->currentPosition <= a.currentPosition;
    }

    bool operator>=(T *pointer) {
        return this->currentPosition >= pointer;
    }

    bool operator>=(const CircularBufferIterator &a) {
        return this->currentPosition >= a.currentPosition;
    }
};

//fixed O(1)
template<typename T>
class CircularBuffer {
private:
    int capacity{};
    int start{}; // indexes
    int finish{};
    T *buffer;

    int endIndex{};

    int quantity{}; // quantity of numbers in the buffer
public:
    CircularBuffer<T>() {
        this->capacity = 0;
        this->start = 0;
        this->finish = 0;
        this->buffer = new T[1];
        this->quantity = 0;
        this->endIndex = 1;
    }

    CircularBuffer<T>(int capacity) {
        this->capacity = capacity;
        this->start = this->capacity - 1;
        this->finish = this->capacity - 1;
        this->buffer = new T[capacity + 1];
        this->quantity = 0;
        this->endIndex = this->capacity;
    }

    ~CircularBuffer() = default;

    bool empty() {
    	//todo one return
        if (this->quantity == 0)
            return true;
        else return false;
    }

    bool full() {
        if (this->quantity == this->capacity && this->capacity != 0) return true;
        else return false;
    }

    void addFirst(T value) {
        if (this->empty()) {
            this->finish = this->start;
        } else if (this->full()) {
            this->start = (this->start - 1 + this->capacity + 1) % (this->capacity + 1);
            this->finish = (this->finish - 1 + this->capacity + 1) % (this->capacity + 1);
        } else {
            this->start = (this->start - 1 + this->capacity + 1) % (this->capacity + 1);

        }

        this->endIndex = (this->finish + 1) % (this->capacity + 1);

        this->buffer[this->start] = value;

        if (this->quantity + 1 <= this->capacity) this->quantity++;

        if (this->start == this->finish && this->quantity > 1) {
            this->finish = (this->finish - 1 + this->capacity) % (this->capacity + 1);
        }
    }

    void delFirst() {
        if (this->empty()) {
            throw std::logic_error("Nothing to delete");
        } else {
            this->quantity--;
            this->start = (this->start + 1) % (this->capacity + 1);
        }
    }

    T first() {
        return this->buffer[this->start];
    }

    void addLast(T value) {
        if (this->empty()) {
            this->buffer[this->finish] = value;
        } else {
            this->finish = (this->finish + 1) % (this->capacity + 1);
            this->buffer[this->finish] = value;
        }
        this->endIndex = (this->finish + 1) % (this->capacity + 1);
        if (this->quantity + 1 <= this->capacity) this->quantity++;
    }

    void delLast() {
        if (this->empty()) {
            throw std::logic_error("Nothing to delete");
        } else {
            this->quantity--;
            if (this->quantity == 0) {
                this->finish = this->start;
            } else {
                this->finish = (this->finish - 1 + this->capacity) % (this->capacity + 1);;
            }

            this->endIndex = (this->finish + 1) % (this->capacity + 1);
        }
    }

    T last() {
        return this->buffer[this->finish];
    }

    void changeCapacity(int size) {
        if (size < this->quantity) {
            throw std::logic_error("Size is lower than quantity of numbers");
        }

        T *temp = new T[size];
        for (int i = 0; i < this->quantity; i++) {
            temp[i] = this->buffer[(this->start + i) % this->capacity];
        }
        //todo delete[]
        delete this->buffer;
        this->buffer = temp;
        this->start = 0;
        this->finish = this->quantity - 1;
        this->endIndex = (this->finish + 1) % (this->capacity + 1);
        this->capacity = size;
    }
    //todo more information in exception
    //todo range_error
    T operator[](int index) const {
        if (index < this->quantity) {
            return this->buffer[(this->start + index) % (this->capacity + 1)];
        } else {
            throw std::logic_error("Wrong index");
        }
    }

    T &operator[](int index) {
        if (index < this->quantity) {
            return this->buffer[(this->start + index) % (this->capacity + 1)];
        } else {
            throw std::logic_error("Wrong index");
        }
    }

    CircularBufferIterator<T> begin() const {
        return CircularBufferIterator<T>(this->buffer + this->start,
                                         this->buffer,
                                         this->buffer + this->capacity
        );
    }

    CircularBufferIterator<T> end() const {
        return CircularBufferIterator<T>(this->buffer + this->endIndex,
                                         this->buffer,
                                         this->buffer + this->capacity

        );
    }
};
