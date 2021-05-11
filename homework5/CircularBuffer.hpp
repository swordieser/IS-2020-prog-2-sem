template<typename T>
//todo without inheritacne from std::iterator
class CircularBufferIterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
    T *position;

    CircularBufferIterator(T *position) {
        this->position = position;
    }

    T &operator*() {
        return *this->position;
    };

    T *operator->() {
        return this->position;
    }

    CircularBufferIterator &operator++() {
        ++this->position;
        return *this;
    }

    CircularBufferIterator &operator--() {
        this->position--;
        return *this;
    }

    CircularBufferIterator operator-(typename std::iterator<std::random_access_iterator_tag, T>::difference_type iter) {
        return CircularBufferIterator(this->position - iter);
    }

    bool operator==(const CircularBufferIterator &a) const {
        return this->position == a.position;
    }

    bool operator!=(const CircularBufferIterator &a) const {
        return this->position != a.position;
    }

    typename std::iterator<std::random_access_iterator_tag, T>::difference_type
    operator-(const CircularBufferIterator<T> &iter) {
        return this->position - iter.position;
    }

    typename std::iterator<std::random_access_iterator_tag, T>::difference_type
    operator+(CircularBufferIterator &iter) {
        return this->position + iter.position;
    }

    CircularBufferIterator operator+(typename std::iterator<std::random_access_iterator_tag, T>::difference_type iter) {
        return CircularBufferIterator(this->position + iter);
    }

    bool operator<(const CircularBufferIterator &a) {
        return this->position < a.position;
    }

    bool operator<(T *pointer) {
        return this->position < pointer;
    }

    bool operator>(T *pointer) {
        return this->position > pointer;
    }

    bool operator<=(T *pointer) {
        return this->position <= pointer;
    }

    bool operator>=(T *pointer) {
        return this->position >= pointer;
    }

    bool operator<=(const CircularBufferIterator &a) {
        return this->position <= a.position;
    }

    bool operator>(const CircularBufferIterator &a) {
        return this->position > a.position;
    }

    bool operator>=(const CircularBufferIterator &a) {
        return this->position >= a.position;
    }

    CircularBufferIterator &
    operator+=(typename std::iterator<std::random_access_iterator_tag, T>::difference_type iter) {
        this->position += iter;
        return *this;
    }

    CircularBufferIterator &
    operator-=(typename std::iterator<std::random_access_iterator_tag, T>::difference_type iter) {
        this->position -= iter;
        return *this;
    }

    CircularBufferIterator &operator=(const CircularBufferIterator &iter) {
        this->position = iter.position;
        return *this;
    }

    CircularBufferIterator &operator=(T *iter) {
        this->position = iter;
        return *this;
    }
};

//todo O(1)
template<typename T>
class CircularBuffer {
private:
    int capacity{};
    int start{}; // indexes
    int finish{};
    T *buffer;

    int quantity{}; // quantity of numbers in the buffer
public:
    CircularBuffer<T>() {
        this->capacity = 0;
        this->start = 0;
        this->finish = 0;
        this->buffer = new T[0];
        this->quantity = 0;
    }

    CircularBuffer<T>(int capacity) {
        this->capacity = capacity;
        this->start = 0;
        this->finish = 0;
        this->buffer = new T[capacity];
        this->quantity = 0;
    }

    bool empty() {
        if (this->quantity == 0)
        	return true;
        else return false;
    }

    bool full() {
        if (this->quantity == this->capacity && this->capacity != 0) return true;
        else return false;
    }

    void addFirst(T value) {
        if (this->full()) {
            for (int i = this->finish; i >= this->start; i--) {
                this->buffer[i % this->capacity] = this->buffer[(i - 1) % this->capacity];
            }
            this->buffer[this->start] = value;
        } else if (this->empty()) {
            this->buffer[this->start] = value;
            this->quantity++;
        } else {
            this->finish++;
            for (int i = this->finish; i >= this->start; i--) {
                this->buffer[i % this->capacity] = this->buffer[(i - 1) % this->capacity];
            }
            this->buffer[this->start] = value;
            this->quantity++;
        }

    }

    void delFirst() {
        if (this->empty()) {
            throw std::logic_error("Nothing to delete");
        } else {
            T *temp = new T[this->capacity];
            for (int i = 0; i < this->quantity; i++) {
                temp[i] = this->buffer[this->start + 1 + i];
            }
            delete this->buffer;
            this->buffer = temp;
            this->quantity--;
            this->start = 0;
            this->finish = this->quantity - 1;
        }
    }

    T first() {
        return this->buffer[this->start];
    }

    void addLast(T value) {
        if (this->empty()) {
            this->quantity++;
            this->buffer[this->finish] = value;
        } else {
            this->finish++;
            this->buffer[this->finish] = value;
            this->quantity++;
        }
    }

    void delLast() {
        if (this->empty()) {
            throw std::logic_error("Nothing to delete");
        } else {
            T *temp = new T[this->capacity];
            for (int i = 0; i < this->quantity - 1; i++) {
                temp[i] = this->buffer[this->start + i];
            }
            delete this->buffer;
            this->buffer = temp;
            this->quantity--;
            this->start = 0;
            if (this->quantity == 0) {
                this->finish = 0;
            } else {
                this->finish = this->quantity - 1;
            }
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
        delete this->buffer;
        this->buffer = temp;
        this->start = 0;
        this->finish = this->quantity - 1;
        this->capacity = size;
    }

    T operator[](int index) const {
        if (index < this->quantity) {
            return this->buffer[(this->start + index) % this->capacity];
        } else {
            throw std::logic_error("Wrong index");
        }
    }

    T &operator[](int index) {
        if (index < this->quantity) {
            return this->buffer[(this->start + index) % this->capacity];
        } else {
            throw std::logic_error("Wrong index");
        }
    }

    CircularBufferIterator<T> begin() const {
        return CircularBufferIterator<T>(this->buffer + this->start);
    }

    CircularBufferIterator<T> end() const {
        return CircularBufferIterator<T>(this->buffer + this->finish + 1);
    }
};
