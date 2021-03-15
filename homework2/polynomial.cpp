#include "polynomial.h"

polynomial::polynomial() {
    this->odds = (int *) malloc(sizeof(int));
    *this->odds = 0;
    this->degree = (int *) malloc(sizeof(int));
    *this->degree = 0;
    this->size = (int *) malloc(sizeof(int));
    *this->size = 1;
}

polynomial::polynomial(int min, int max, int *odd) {
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

polynomial::polynomial(const polynomial &p) {
    this->size = (int *) malloc(sizeof(int));
    *this->size = *p.size;

    this->odds = (int *) malloc((*this->size) * sizeof(int));
    this->degree = (int *) malloc((*this->size) * sizeof(int));

    for (int i = 0; i < *this->size; i++) {
        this->degree[i] = p.degree[i];
        this->odds[i] = p.odds[i];
    }
}

//polynomial::~polynomial() = default;

polynomial &polynomial::operator=(const polynomial &p) {
    this->odds = p.odds;
    this->degree = p.degree;
    this->size = p.size;
    return *this;
};

bool operator==(const polynomial &p1, const polynomial &p2) {
    stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    return ss1.str() == ss2.str();
};

bool operator!=(const polynomial &p1, const polynomial &p2) {
    return !(p1 == p2);
};

polynomial operator+(const polynomial &p1, const polynomial &p2) {
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

    return polynomial(min, max, odds);
};

polynomial operator-(const polynomial &p) {
    for (int i = 0; i < *p.size; i++) {
        p.odds[i] *= -1;
    }
    return p;
};

polynomial operator-(const polynomial &p1, const polynomial &p2) {
    return p1 + (-p2);
};

polynomial operator+=(polynomial &p1, const polynomial &p2) {
    p1 = p1 + p2;
    return p1;
};

polynomial operator-=(polynomial &p1, const polynomial &p2) {
    p1 = p1 - p2;
    return p1;
};

polynomial operator*(const polynomial &p, int number) {
    int temp_odds[*p.size];
    for (int i = 0; i < *p.size; i++) {
        temp_odds[i] = p.odds[i] * number;
    }
    return polynomial(p.degree[0], p.degree[*p.size - 1], temp_odds);
};

polynomial operator*(int number, const polynomial &p) {
    return p * number;
}

polynomial operator*(const polynomial &p1, const polynomial &p2) {
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
    int max = temp_degree[temp_size-1];
    int s = max - min + 1;
    int polynomial_degree[s], polynomial_odds[s];
    int tmp = min;
    for (int i = 0; i < s; i++){
        polynomial_degree[i] = tmp;
        polynomial_odds[i] = 0;
        tmp++;
    }

    for (int i = 0; i < s; i++){
        for (int j =0; j < temp_size; j++){
            if (temp_degree[j] == polynomial_degree[i]){
                polynomial_odds[i] += temp_odds[j];
            }
        }
    }

    return polynomial(min, max, polynomial_odds);
};

polynomial operator/(const polynomial &p, int number) {
    int temp_odds[*p.size];
    for (int i = 0; i < *p.size; i++) {
        temp_odds[i] = p.odds[i] / number;
    }
    return polynomial(p.degree[0], p.degree[*p.size - 1], temp_odds);
};

polynomial operator*=(polynomial &p1, const polynomial &p2) {
    p1 = p1*p2;
    return p1;
};

polynomial operator/=(polynomial &p, int number) {
    p = p / number;
    return p;
};

std::stringstream &operator<<(std::stringstream &out, const polynomial &p) {
    int temp_size = *p.size;
    if (temp_size == 1 and p.odds[0] == 0) {
        out << "0";
    } else {
        for (int i = temp_size - 1; i >= 0; i--) {
            if (p.odds[i] != 0) {
                if (i < temp_size - 1 && p.odds[i] > 0) {
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
    for (int i = 0; i < *p.size; i++){
        if (p.odds[i]==0){
            temp++;
        }
    }
    if (temp==*p.size && out.str().empty()){
        out << "0";
    }
    return out;
};

//std::stringstream &operator>>(std::stringstream &in, const polynomial &p) {
//
//};

//int &polynomial::operator[](int i) {
//
//};

//int get(int number){
//
//}
