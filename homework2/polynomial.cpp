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
    this->odds = p.odds;
    this->degree = p.degree;
    this->size = p.size;
}

//polynomial::~polynomial() = default;

polynomial &polynomial::operator=(const polynomial &p) = default;

bool operator==(const polynomial &p1, const polynomial &p2) {
    bool equal = true;
    for (int i = 0; i < *p1.size; i++){
        if ((p1.degree[i] != p2.degree[i]) || (p1.odds[i] != p2.odds[i])){
            equal = false;
            break;
        }
    }
    return equal;
};

bool operator!=(const polynomial &p1, const polynomial &p2) {
    return !(p1==p2);
};

//polynomial operator+(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator-(int number) {
//
//};

//polynomial &polynomial::operator-(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator+=(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator-=(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator*(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator/(int number) {
//
//};

//polynomial &polynomial::operator*=(const polynomial &p1, const polynomial &p2) {
//
//};

//polynomial &polynomial::operator/=(int number) {
//
//};

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
    return out;
};

//std::stringstream &operator>>(std::stringstream &in, const polynomial &p) {
//
//};

//int &polynomial::operator[](int i) {
//
//};
