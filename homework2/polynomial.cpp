#include "polynomial.h"

int *polynomial::get_degree() const {
    return this->degree;
}

int *polynomial::get_odds() const {
    return this->odds;
}

int polynomial::get_size() const {
    return this->size;
}

polynomial::polynomial() {
    this->odds = new int[1]{0};
    this->degree = new int[1]{0};
    this->size = 1;
}

polynomial::polynomial(int min, int max, int *odds) {
    int s = max - min + 1; //size
    this->degree = new int[s];
    int d = min;
    for (int i = 0; i < s; i++) {
        this->degree[i] = d;
        d++;
    }
    this->odds = odds;
    this->size = s;
}

//polynomial::polynomial(const polynomial &p) {
//
//}

//polynomial::~polynomial() = default;

//polynomial &polynomial::operator=(const polynomial &p) {
//
//};

//bool &polynomial::operator==(const polynomial &p) {
//
//};

//bool &polynomial::operator!=(const polynomial &p) {
//
//};

//polynomial &polynomial::operator+(const polynomial &p) {
//
//};

//polynomial &polynomial::operator-() {
//
//};

//polynomial &polynomial::operator-(const polynomial &p) {
//
//};

//polynomial &polynomial::operator+=(const polynomial &p) {
//
//};

//polynomial &polynomial::operator-=(const polynomial &p) {
//
//};

//polynomial &polynomial::operator*(const polynomial &p) {
//
//};

//polynomial &polynomial::operator/(int number) {
//
//};

//polynomial &polynomial::operator*=(const polynomial &p) {
//
//};

//polynomial &polynomial::operator/=(int number) {
//
//};

std::stringstream &operator<<(std::stringstream &out, const polynomial &p) {
    int *temp_odds = p.get_odds();
    int *temp_degree = p.get_degree();
    int temp_size = p.get_size();
    if (temp_size == 1 and temp_odds[0] == 0) {
        out << "0";
    } else {
        for (int i = temp_size - 1; i >= 0; i--) {
            if (temp_odds[i] != 0) {
                if (i < temp_size - 1 && temp_odds[i] > 0) {
                    out << "+";
                }

                if (temp_odds[i] == -1 && temp_degree[i] != 0) {
                    out << "-";
                } else if (temp_odds[i] == 1 && temp_degree[i] != 0){
                    out << "";
                } else {
                    out << temp_odds[i];
                }

                if (temp_degree[i] != 0) {
                     out << "x";
                    if (temp_degree[i] != 1) {
                        out << "^" << temp_degree[i];
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
