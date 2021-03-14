#ifndef IS_2020_PROG_2_SEM_POLYNOMIAL_H
#define IS_2020_PROG_2_SEM_POLYNOMIAL_H

#include "vector"
#include "cmath"
#include "sstream"

using namespace std;

class polynomial {
private:
//    vector<int>* degree;
//    vector<int>* odds;
    int* degree;
    int* odds;
    int* size;
public:
    polynomial();
    polynomial(int min, int max,  int* odd);
    polynomial(const polynomial &p);
//    ~polynomial();
    polynomial &operator=(const polynomial &p);
    friend bool operator==(const polynomial &p1, const polynomial &p2);
    friend bool operator!=(const polynomial &p1, const polynomial &p2);
    friend polynomial operator+(const polynomial &p1, const polynomial &p2);
//    polynomial &operator-(int number);
//    polynomial &operator-(const polynomial &p1, const polynomial &p2);
//    polynomial &operator+=(const polynomial &p1, const polynomial &p2);
//    polynomial &operator-=(const polynomial &p1, const polynomial &p2);
//    polynomial &operator*(const polynomial &p1, const polynomial &p2);
//    polynomial &operator/(int number);
//    polynomial &operator*=(const polynomial &p1, const polynomial &p2);
//    polynomial &operator/=(int number);
    friend std::stringstream &operator<< (std::stringstream &out, const polynomial &p);
//    friend std::stringstream &operator>> (std::istream &in, const polynomial &p);
//    int &operator[](int i);
};



#endif
