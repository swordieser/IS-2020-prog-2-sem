#ifndef IS_2020_PROG_2_SEM_POLYNOMIAL_H
#define IS_2020_PROG_2_SEM_POLYNOMIAL_H

#include "vector"
#include "cmath"
#include "sstream"

using namespace std;

class polynomial {
private:
    int* degree;
    int* odds;
    int size;
public:
    int* get_degree() const;
    int* get_odds() const;
    int get_size() const;
    polynomial();
    polynomial(int min, int max, int* odds);
//    polynomial(const polynomial &p);
//    ~polynomial();
//    polynomial &operator=(const polynomial &p);
//    bool &operator==(const polynomial &p);
//    bool &operator!=(const polynomial &p);
//    polynomial &operator+(const polynomial &p);
//    polynomial &operator-();
//    polynomial &operator-(const polynomial &p);
//    polynomial &operator+=(const polynomial &p);
//    polynomial &operator-=(const polynomial &p);
//    polynomial &operator*(const polynomial &p);
//    polynomial &operator/(int number);
//    polynomial &operator*=(const polynomial &p);
//    polynomial &operator/=(int number);
    friend std::stringstream &operator<< (std::stringstream &out, const polynomial &p);
//    friend std::istream &operator>> (std::istream &in, const polynomial &p);
//    int &operator[](int i);
};



#endif
