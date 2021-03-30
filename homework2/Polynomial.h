#ifndef IS_2020_PROG_2_SEM_POLYNOMIAL_H
#define IS_2020_PROG_2_SEM_POLYNOMIAL_H

#include "vector"
#include "cmath"
#include "sstream"
#include <algorithm>


using namespace std;

class Polynomial {
private:
    int *degree;
    int *odds;
    int size;
public:
    Polynomial();

    Polynomial(int min, int max, int *odd);

    Polynomial(const Polynomial &p);

    ~Polynomial();

    Polynomial &operator=(const Polynomial &p);

    friend bool operator==(const Polynomial &p1, const Polynomial &p2);

    friend bool operator!=(const Polynomial &p1, const Polynomial &p2);

    friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);

    Polynomial operator-() const;

    friend Polynomial operator-(const Polynomial &p1, const Polynomial &p2);

    Polynomial operator+=(const Polynomial &p);

    Polynomial operator-=(const Polynomial &p);

    friend Polynomial operator*(const Polynomial &p, int number);

    friend Polynomial operator*(int number, const Polynomial &p);

    friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);

    Polynomial operator/(int number);

    Polynomial &operator*=(const Polynomial &p);

    Polynomial &operator/=(int number);

    friend std::stringstream &operator<<(std::stringstream &out, const Polynomial &p);

    int operator[](int number) const;

    int &operator[](int i);

    double get(double number);
};


#endif
