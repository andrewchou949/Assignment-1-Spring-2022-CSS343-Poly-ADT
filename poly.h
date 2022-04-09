// ---------------------------------------poly.h-------------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 03/30/2022
// Date of Last Modification: 04/08/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .h file for polynomial class contain the contract interface for poly.cpp file
// ----------------------------------------------------------------------------------------------------

#ifndef ASS1_POLY_H
#define ASS1_POLY_H

#include <iostream>

using namespace std;

class Poly {

    // friend ostream function
    // to print out polynomial
    friend ostream& operator<<(ostream& out, const Poly& pol);

    // friend istream function
    // to set coeff multiple time until user typed -1
    friend istream& operator>>(istream& is, Poly& pol);

public:
    // default constructor
    Poly();

    // copy constructor
    Poly(const Poly& oldObject);

    // constructor with one param (coeff)
    explicit Poly(int x);

    // constructor with two param (coeff, power) order
    Poly(int x, int y);

    // accessor method
    int getCoeff(int x) const;
     
    // mutator method;
    void setCoeff(int x, int y);

    // perform + of two polynomial, param is rhs
    Poly operator+(const Poly& pol);

    // perform + of two things, param is rhs and is an integer type
    Poly operator+(int x);

    // perform - of two polynomial, param is rhs
    Poly operator-(const Poly& pol);

    // perform - of two things, param is rhs and is an integer type
    Poly operator-(int x);

    // perform * of two polynomial, param is rhs
    Poly operator*(const Poly& pol);

    // perform * of two things, param is rhs and is an integer type
    Poly operator*(int x);

    // perform +=, return result of addition
    Poly operator+=(const Poly& pol);

    // perform -=, return result of subtraction (param is the rhs)
    Poly operator-=(const Poly& pol);

    // perform *=, return result of multiplication
    Poly operator*=(const Poly& pol);

    // check if two polynomial are the same, true if equal
    bool operator==(const Poly& pol);

    // check if two polynomial are not the same, true if not equal
    bool operator!=(const Poly& pol);

    // assignment operator, lhs will have the rhs value after call
    Poly& operator=(const Poly& pol);

    // virtual destructor function, destroy everything of the object called
    virtual ~Poly();

private:

    // ptr to array
    int* headPtr;

    // current maximum size of array
    // container to keep track of current item in array, 
    // used as index when looping through array
    int itemCount = 0;

};
#endif