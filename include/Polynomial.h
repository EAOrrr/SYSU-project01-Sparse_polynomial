#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include"linkedList.h"
#include<cmath>

class Polynomial:public LinkedList{
    public:
        Polynomial(); 
        Polynomial(Node* head, size_t size=0);
        Polynomial(const Polynomial& other);
        Polynomial(Polynomial&& other);
        void insert(int key, double value);
        Polynomial operator=(const Polynomial& other);
        Polynomial operator=(Polynomial&& other);
        Polynomial operator+(const Polynomial& other);
        Polynomial operator-(const Polynomial& other);
        Polynomial operator+=(const Polynomial& other);
        Polynomial operator-=(const Polynomial& other);
        Polynomial operator*(const Polynomial& other);
        Polynomial operator*=(const Polynomial& other);
        double compute(double x) const;
        void derive();
        void printPoly(std::ostream& os) const;
};
#endif