#include "Polynomial.h"

Polynomial::Polynomial() {
    //fixed new not malloc
    this->odds = new int;
    *this->odds = 0;
    this->degree = new int;
    *this->degree = 0;
    this->size = 1;
}

Polynomial::Polynomial(int min, int max, int *odd) {
    int s = max - min + 1;

    this->degree = new int[s];
    this->odds = new int[s];
    this->size = s;

    int d = min;
    for (int i = 0; i < s; i++) {
        this->degree[i] = d;
        this->odds[i] = *odd;
        d++;
        odd++;
    }
}

Polynomial::Polynomial(const Polynomial &p) {
    this->size = p.size;

    this->odds = new int[this->size];
    this->degree = new int[this->size];

    *this = p;
}

//fixed delete
Polynomial::~Polynomial() {
    delete this->degree;
    delete this->odds;
}

Polynomial &Polynomial::operator=(const Polynomial &p) {
    //fixed make copy
    this->size = p.size;

    this->odds = new int[this->size];
    this->degree = new int[this->size];

    for (int i = 0; i < this->size; i++) {
        this->degree[i] = p.degree[i];
        this->odds[i] = p.odds[i];
    }
    return *this;
}


bool operator==(const Polynomial &p1, const Polynomial &p2) {
    stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    return ss1.str() == ss2.str();
}

bool operator!=(const Polynomial &p1, const Polynomial &p2) {
    return !(p1 == p2);
}

//fixed + from +=
Polynomial operator+(const Polynomial &p1, const Polynomial &p2) {
    auto p = Polynomial();
    p += p1;
    p += p2;
    return p;
}

Polynomial Polynomial::operator-() const {
    int *temp_odds = new int[this->size];
    for (int i = 0; i < this->size; i++) {
        temp_odds[i] = -this->odds[i];
    }
    return Polynomial(this->degree[0], this->degree[this->size - 1], temp_odds);
}

//fixed without new object
Polynomial operator-(const Polynomial &p1, const Polynomial &p2) {
    return p1 + (-p2);
}

Polynomial Polynomial::operator+=(const Polynomial &p) {
    int min = this->degree[0] <= p.degree[0] ? this->degree[0] : p.degree[0];
    int max =
            this->degree[this->size - 1] >= p.degree[p.size - 1] ? this->degree[this->size - 1] : p.degree[p.size - 1];
    int temp_size = max - min + 1;
    int temp_odds[temp_size];
    int temp_degree = min;
    for (int i = 0; i < temp_size; i++) {
        temp_odds[i] = 0;
        for (int j = 0; j < this->size; j++) {
            if (this->degree[j] == temp_degree) {
                temp_odds[i] += this->odds[j];
            }
        }
        for (int j = 0; j < p.size; j++) {
            if (p.degree[j] == temp_degree) {
                temp_odds[i] += p.odds[j];
            }
        }
        temp_degree++;
    }

    *this = Polynomial(min, max, temp_odds);
    return *this;
}

Polynomial Polynomial::operator-=(const Polynomial &p) {
    *this = *this - p;
    return *this;
}

Polynomial operator*(const Polynomial &p, int number) {
    int temp_odds[p.size];
    int i = 0;
    //fixed for_each
    for_each(temp_odds, temp_odds + p.size, [number, p, &i](int &n) {
        n = p.odds[i] * number;
        i++;
    });
    return Polynomial(p.degree[0], p.degree[p.size - 1], temp_odds);
}

Polynomial operator*(int number, const Polynomial &p) {
    return p * number;
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2) {
    int temp_size = p1.size * p2.size;
    int temp_odds[temp_size], temp_degree[temp_size];
    int iter = 0;
    for (int i = 0; i < p1.size; i++) {
        for (int j = 0; j < p2.size; j++) {
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
}

Polynomial Polynomial::operator/(int number) {
    auto temp = *this;
    for_each(temp.odds, temp.odds + temp.size, [&](int &n) { n /= number; });
    return temp;
}

Polynomial &Polynomial::operator*=(const Polynomial &p) {
    *this = *this * p;
    return *this;
}

Polynomial &Polynomial::operator/=(int number) {
    *this = *this / number;
    return *this;
}

std::stringstream &operator<<(std::stringstream &out, const Polynomial &p) {
    int temp_size = p.size;
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
    for (int i = 0; i < p.size; i++) {
        if (p.odds[i] == 0) {
            temp++;
        }
    }
    if (temp == p.size && out.str().empty()) {
        out << "0";
    }
    return out;
}

int Polynomial::operator[](int number) const {
    if (number > this->degree[0] && number < this->degree[this->size - 1]) {
        int index = 0;
        for (int i = 0; i < this->size; i++) {
            if (number == this->degree[i]) {
                break;
            }
            index++;
        }
        return this->odds[index];
    } else {
        return 0;
    }
}

int &Polynomial::operator[](int number) {
    if (number > this->degree[0] && number < this->degree[this->size - 1]) {
        return this->odds[number];
    } else if (number < this->degree[0]) {
        int max = this->degree[this->size - 1];
        int min = number;
        int temp_size = max - min + 1;
        int temp_odds[temp_size];
        for (int i = 0; i < temp_size; i++) {
            temp_odds[i] = 0;
        }

        for (int i = 1; i < this->size; i++) {
            temp_odds[temp_size - i] = this->odds[this->size - i];
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

        for (int i = 0; i < this->size; i++) {
            temp_odds[i] = this->odds[i];
        }

        *this = Polynomial(min, max, temp_odds);
        return this->odds[this->size - 1];
    }
}

double Polynomial::get(double number) {
    //fixed no *
    double answer = 0;
    double x = pow(number, this->degree[0]);
    for (int i = 0; i < this->size; i++) {
        answer += this->odds[i] * x;
        x *= number;
    }
    return answer;
}


