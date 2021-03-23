#include "Polynomial.h"

Polynomial::Polynomial() {
	//todo new not malloc
    this->odds = (int *) malloc(sizeof(int));
    *this->odds = 0;
    this->degree = (int *) malloc(sizeof(int));
    *this->degree = 0;
    this->size = (int *) malloc(sizeof(int));
    *this->size = 1;
}

Polynomial::Polynomial(int min, int max, int *odd) {
    int s = max - min + 1;

    this->degree = (int *) malloc(s * sizeof(int));
    this->odds = (int *) malloc(s * sizeof(int));
    this->size = (int *) malloc(sizeof(int));
    *this->size = s;

    int d = min;
    for (int i = 0; i < s; i++) {
        this->degree[i] = d;
        this->odds[i] = *odd;
        d++;
        odd++;
    }
}

Polynomial::Polynomial(const Polynomial &p) {
    this->size = (int *) malloc(sizeof(int));
    *this->size = *p.size;

    this->odds = (int *) malloc((*this->size) * sizeof(int));
    this->degree = (int *) malloc((*this->size) * sizeof(int));

    for (int i = 0; i < *this->size; i++) {
        this->degree[i] = p.degree[i];
        this->odds[i] = p.odds[i];
    }
}

//todo delete
Polynomial::~Polynomial() = default;

Polynomial &Polynomial::operator=(const Polynomial &p) {
    //todo make copy
    this->odds = p.odds;
    this->degree = p.degree;
    this->size = p.size;
    return *this;
};


bool operator==(const Polynomial &p1, const Polynomial &p2) {
    stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    return ss1.str() == ss2.str();
};

bool operator!=(const Polynomial &p1, const Polynomial &p2) {
    return !(p1 == p2);
};

//todo + from +=
Polynomial operator+(const Polynomial &p1, const Polynomial &p2) {
    int min = p1.degree[0] <= p2.degree[0] ? p1.degree[0] : p2.degree[0];
    int max = p1.degree[*p1.size - 1] >= p2.degree[*p2.size - 1] ? p1.degree[*p1.size - 1] : p2.degree[*p2.size - 1];
    int size = max - min + 1;
    int odds[size];
    int temp_degree = min;
    for (int i = 0; i < size; i++) {
        odds[i] = 0;
        for (int j = 0; j < *p1.size; j++) {
            if (p1.degree[j] == temp_degree) {
                odds[i] += p1.odds[j];
            }
        }
        for (int j = 0; j < *p2.size; j++) {
            if (p2.degree[j] == temp_degree) {
                odds[i] += p2.odds[j];
            }
        }
        temp_degree++;
    }

    return Polynomial(min, max, odds);
};

Polynomial operator-(const Polynomial &p) {
    auto c = p;
    for (int i = 0; i < *c.size; i++) {
        c.odds[i] *= -1;
    }
    return c;
};
//todo without new object
Polynomial operator-(const Polynomial &p1, const Polynomial &p2) {
    return p1 + (-p2);
};

Polynomial operator+=(Polynomial &p1, const Polynomial &p2) {
    p1 = p1 + p2;
    return p1;
};

Polynomial operator-=(Polynomial &p1, const Polynomial &p2) {
    p1 = p1 - p2;
    return p1;
};

Polynomial operator*(const Polynomial &p, int number) {
    int temp_odds[*p.size];
    //todo for_each
    for (int i = 0; i < *p.size; i++) {
        temp_odds[i] = p.odds[i] * number;
    }
    return Polynomial(p.degree[0], p.degree[*p.size - 1], temp_odds);
};

Polynomial operator*(int number, const Polynomial &p) {
    return p * number;
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2) {
    int temp_size = *p1.size * *p2.size;
    int temp_odds[temp_size], temp_degree[temp_size];
    int iter = 0;
    for (int i = 0; i < *p1.size; i++) {
        for (int j = 0; j < *p2.size; j++) {
            temp_odds[iter] = p1.odds[i] * p2.odds[j];
            temp_degree[iter] = p1.degree[i] + p2.degree[j];
            iter++;
        }
    }
    int min = temp_degree[0];
    int max = temp_degree[temp_size - 1];
    int s = max - min + 1;
    int polynomial_degree[s], polynomial_odds[s];
    int tmp = min;
    for (int i = 0; i < s; i++) {
        polynomial_degree[i] = tmp;
        polynomial_odds[i] = 0;
        tmp++;
    }

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < temp_size; j++) {
            if (temp_degree[j] == polynomial_degree[i]) {
                polynomial_odds[i] += temp_odds[j];
            }
        }
    }

    return Polynomial(min, max, polynomial_odds);
};

Polynomial operator/(const Polynomial &p, int number) {
    int temp_odds[*p.size];
    for (int i = 0; i < *p.size; i++) {
        temp_odds[i] = p.odds[i] / number;
    }
    return Polynomial(p.degree[0], p.degree[*p.size - 1], temp_odds);
};

Polynomial operator*=(Polynomial &p1, const Polynomial &p2) {
    p1 = p1 * p2;
    return p1;
};

Polynomial operator/=(Polynomial &p, int number) {
    p = p / number;
    return p;
};

std::stringstream &operator<<(std::stringstream &out, const Polynomial &p) {
    int temp_size = *p.size;
    if (temp_size == 1 and p.odds[0] == 0) {
        out << "0";
    } else {
        for (int i = temp_size - 1; i >= 0; i--) {
            if (p.odds[i] != 0) {
                if (i < temp_size - 1 && p.odds[i] > 0 && !out.str().empty() && out.str().back() != '\n') {
                    out << "+";
                }

                if (p.odds[i] == -1 && p.degree[i] != 0) {
                    out << "-";
                } else if (p.odds[i] == 1 && p.degree[i] != 0) {
                    out << "";
                } else {
                    out << p.odds[i];
                }

                if (p.degree[i] != 0) {
                    out << "x";
                    if (p.degree[i] != 1) {
                        out << "^" << p.degree[i];
                    }
                }

            }
        }
    }
    int temp = 0;
    for (int i = 0; i < *p.size; i++) {
        if (p.odds[i] == 0) {
            temp++;
        }
    }
    if (temp == *p.size && out.str().empty()) {
        out << "0";
    }
    return out;
};

int &Polynomial::operator[](int number) const {
    if (number > this->degree[0] && number < this->degree[*this->size - 1]) {
        int index = 0;
        for (int i = 0; i < *this->size; i++) {
            if (number == this->degree[i]) {
                break;
            }
            index++;
        }
        return this->odds[index];
    } else {
        int *a = new int;
        *a = 0;
        return *a;
    }
}

int &Polynomial::operator[](int number) {
    if (number > this->degree[0] && number < this->degree[*this->size - 1]) {
        const Polynomial p = *this;
        return p[number];
    } else if (number < this->degree[0]) {
        int max = this->degree[*this->size - 1];
        int min = number;
        int temp_size = max - min + 1;
        int temp_odds[temp_size];
        for (int i = 0; i < temp_size; i++) {
            temp_odds[i] = 0;
        }

        for (int i = 1; i < *this->size; i++) {
            temp_odds[temp_size - i] = this->odds[*this->size - i];
        }

        *this = Polynomial(min, max, temp_odds);
        return this->odds[0];
    } else {
        int max = number;
        int min = this->degree[0];
        int temp_size = max - min + 1;
        int temp_odds[temp_size];

        for (int i = 0; i < temp_size; i++) {
            temp_odds[i] = 0;
        }

        for (int i = 0; i < *this->size; i++) {
            temp_odds[i] = this->odds[i];
        }

        *this = Polynomial(min, max, temp_odds);
        return this->odds[*this->size - 1];
    }
};

double &Polynomial::get(double number) {
    //todo no *
    auto *answer = new double;
    *answer = 0;
    for (int i = 0; i < *this->size; i++) {
        *answer += this->odds[i] * pow(number, this->degree[i]);
    }
    return *answer;
}
