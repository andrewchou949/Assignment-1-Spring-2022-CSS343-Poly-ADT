// ---------------------------------------poly.cpp-----------------------------------------------------
// -
// Name: Andrew Chou
// Course Section: CSS 343 B
// Creation Date: 03/30/2022
// Date of Last Modification: 04/08/2022
// ----------------------------------------------------------------------------------------------------
// Purpose: .cpp file for polynomial class, by taking input from user, creating polynomial function
//          store value in array storage
//          have function of setCoeff(need new coeff, power position to change), getCoeff(with power)
//          have operater+ - *
//          have operater += -= *= that uses operator + - *
//          have virtual destructor
// ----------------------------------------------------------------------------------------------------

#include "poly.h"
#include <iostream>

using namespace std;

// ----------------------------------ostream<<--------------------------------------------------------
// print polynomial
// post: print the whole polynomial out, 
// if the polynomial are all zeros, print out 0
ostream& operator<<(ostream& out, const Poly& pol) {  
    if (pol.itemCount == 0) {
        return out << "0";
    }
    for (int i = pol.itemCount - 1; i >= 0; i--) {
        if (pol.headPtr[i] > 0) {
            out << " ";
            // if coeff not 1, power > 1
            if (i > 1 && pol.headPtr[i] != 1) {
                out << "+" << pol.headPtr[i] << "x^" << i;
            }
            //if coeff = 1, power > 1
            else if (i > 1 && pol.headPtr[i] == 1) {
                out << "+x^" << i;
            }
            //if coeff = 1 and power = 1
            else if (i == 1 && pol.headPtr[i] == 1) {
                out << "+x";
            }
            //if coeff not 1. power = 1
            else if (i == 1 && pol.headPtr[i] != 1) {
                out << "+" << pol.headPtr[i] << "x";
            }
            // power is 0, only print coeff (x^0 = 1)
            else {
                out << "+" << pol.headPtr[i];
            }
        }
        else if (pol.headPtr[i] < 0) {
            out << " ";
            if (i > 1 && pol.headPtr[i] != -1) {
                out << pol.headPtr[i] << "x^" << i;
            }
            else if (i > 1 && pol.headPtr[i] == -1) {
                out << "-x^" << i;
            }
            else if (i == 1 && pol.headPtr[i] == -1) {
                out << "-x";
            }
            else if (i == 1 && pol.headPtr[i] != 1) {
                out << pol.headPtr[i] << "x";
            }
            // power is 0, only print coeff (x^0 = 1)
            else {
                out << pol.headPtr[i];
            }
        }
    }
    return out;
}
// ----------------------------------default constructor------------------------------------------------
// default constructor (no param)
// post: coeff = 0; power = 0
// zero coeff with zero power
Poly::Poly() {
    this->itemCount = 1; // increment size
    headPtr = new int[itemCount];
    headPtr[0] = 0;
}

// ----------------------------------copy constructor--------------------------------------------------
// copy constructor
// post: current headptr will be of sourceCopy's element
Poly::Poly(const Poly& sourceCopy) {
    // adjust current count to be the count in param (what to be copied)
    this->itemCount = sourceCopy.itemCount;
    // create new array length;
    headPtr = new int[sourceCopy.itemCount];
    // copy all item in the source array
    for (int i = 0; i < sourceCopy.itemCount; i++) {
        headPtr[i] = sourceCopy.headPtr[i];
    }
}

// ----------------------------------constructor (one param)-------------------------------------------
// constructor (one param): param is coeff, power will be zero
// power zero = store at index 0 for array
// post: power is zero, coeff can be any numbers depending on param provided
Poly::Poly(int coeff) {
    this->itemCount = 1;
    headPtr = new int[itemCount];
    headPtr[0] = coeff;
}

// ----------------------------------constructor (two param)-------------------------------------------
// coeff with power specified
// constructor with two param(coeff and power)
// power = x, meaning the coeff is store in index x for array
// post: coeff (first param) will be stored in index x (second param) of array object
Poly::Poly(int coeff, int power) {
    this->itemCount = power + 1; // power is max power of polynomial
    // but array starts from 0 (power of 0), so the total length is power + 1
    headPtr = new int[itemCount];
    // setting all index's value to 0;
    for (int i = 0; i < itemCount; i++) {
        headPtr[i] = 0;
    }
    // set the index of power to be the coeff
    headPtr[power] = coeff;
}

// -------------------------------------accessor--------------------------------------------------------
// function is constant since it does not need to change anything
// post: return the coeff depending of its position in array (position is the param)
// if param is invalid (not inside valid range) return 0;
int Poly::getCoeff(int power) const{
    // exception checking if power (index) is within range
    if (power >= 0 && power <= itemCount - 1) {
        return this->headPtr[power];
    }
    else {
        return 0; // out of range handling
    }
}

// ----------------------------------------mutator------------------------------------------------------
// adding new coeff to array base on position or power provided
// post: new value added to array based on index provided
// if index is negative (invalid), print out error statemetn to console
void Poly::setCoeff(int newCoeff, int pos) {
    // check if the index or power is positive. Only proceed with positive index
    if (pos >= 0) {
        // within range
        if (pos <= this->itemCount - 1) {
            headPtr[pos] = newCoeff;
        }
        // out of range
        // need to create a new array with new length
        else {
            // new container
            // new length is power + 1 (including index 0 position)
            int* newArray = new int[pos + 1];
            // copy old value to new array
            for (int i = 0; i < this->itemCount; i++) {
                newArray[i] = headPtr[i];
            }
            // set default val of 0 to all index between last length to new length
            // unless using this function to set manually
            for (int j = this->itemCount; j < pos + 1; j++) {
                newArray[j] = 0;
            }
            // store the data (for this function call)
            newArray[pos] = newCoeff;

            // deallocate memory to prevent leak
            delete[] headPtr;
            headPtr = nullptr;
            headPtr = newArray;
            newArray = nullptr;
            // update length
            this->itemCount = pos + 1;
        }
    }
    // negative power exception handling
    else {
        cout << "power is invalid, no negative power!";
    }
}

// ------------------------------------operator>>------------------------------------------------------
// set a bunch of coeff and power
// ask user to input a pair of value, first half is the coeff, second is the position or power
// will use the setCoeff function multiple times unless the responses are both -1
// post: add value to array unless condition fulfilled (response no longer -1s)
istream& operator>>(istream& is, Poly& pol) {
    int coeff;
    int power;
    is >> coeff;
    is >> power;
    // when the input is -1 twice, end while loop
    while (coeff != -1 && power != -1) {
        pol.setCoeff(coeff, power);
        // update variable base on answer then go through while loop again
        is >> coeff;
        is >> power;
    }
    return is;
}

// -------------------------------operator+ (with polynomal rhs)----------------------------------------
// add two polynomial together
// post: return the sum object. That sum object contain the array correspond to
//  result of addition of two polynomial
Poly Poly::operator+(const Poly& pol) {
    if (this->itemCount > pol.itemCount) {
        // container for sum with length of the longer polynomial (headPtr)
        Poly sum(0, this->itemCount);
        // copy all value from longer polynomial to sum container
        // copy all info from headPtr to new sum container
        for (int i = 0; i < this->itemCount; i++) {
            sum.headPtr[i] = this->headPtr[i];
        }
        // uses the new sum container (with value from headPtr added), add them with pol
        for (int j = 0; j < pol.itemCount; j++){
            sum.headPtr[j] += pol.headPtr[j];
        }
        return sum;
    }
    else {
        // container for sum with length of the longer polynomial (param)
        Poly sum(0, pol.itemCount);
        // copy all value from longer polynomial to sum container
        for (int i = 0; i < pol.itemCount; i++) {
            sum.headPtr[i] = pol.headPtr[i];
        }
        for (int j = 0; j < this->itemCount; j++) {
            sum.headPtr[j] += this->headPtr[j];
        }
        return sum;
    }
}

// --------------------------------------operator+ (with int)------------------------------------------
// operator+ for handling when rhs is a int type (non-object)
// post: adding polynomial object to integer right hand side
Poly Poly::operator+(int x) {
    this->headPtr[0] += x;
    return *this;
}

// -------------------------------operator+ (with polynomal rhs)----------------------------------------
// minus two polynomial together
// post: return the sub object. That sub object contain the array correspond to
// result of subtraction of two polynomial
Poly Poly::operator-(const Poly& pol) {
    if (this->itemCount > pol.itemCount) {
        // container for sum result with length of the longer polynomial (headPtr)
        Poly sub(0, this->itemCount);
        for (int i = 0; i < this->itemCount; i++) {
            sub.headPtr[i] = this->headPtr[i];
        }
        for (int j = 0; j < pol.itemCount; j++) {
            sub.headPtr[j] -= pol.headPtr[j];
        }
        return sub;
    }
    else {
        // container for sum with length of the longer polynomial (param)
        Poly sub(0, pol.itemCount);
        // copy all value from the headPtr, since that will be used to 
        // subtract other polynomial (pol)
        for (int i = 0; i < this->itemCount; i++) {
            sub.headPtr[i] = this->headPtr[i];
        }
        for (int j = 0; j < pol.itemCount; j++) {
            sub.headPtr[j] -= pol.headPtr[j];
        }
        return sub;
    }
}

// --------------------------------------operator- (with int)------------------------------------------
// operator- to deal when the rhs is int type (non-object)
// post: subtracting polynomial object to the integer right hand side
Poly Poly::operator-(int x) {
    this->headPtr[0] -= x;
    return *this;
}

// -------------------------------operator* (with polynomal rhs)----------------------------------------
// times two polynomial together
// post: return the multiple object. That mult object contain the array correspond to
// result of multiplication of two polynomial
Poly Poly::operator*(const Poly& pol) {
    // if the max power of each polynomial is 3 then the count for result is 6
    int newCount = (this->itemCount + pol.itemCount) - 1;
    // container for multipled polynomial with new length. 
    // other elements in the array is 0 (coeff = 0)
    Poly mult(0, newCount);
    // first polynomial length is bigger than param
    for (int i = 0; i < this->itemCount; i++) {
        if (this->headPtr[i] != 0) {
            for (int j = 0; j < pol.itemCount; j++) {
                mult.headPtr[i + j] += (this->headPtr[i] * pol.headPtr[j]);
            }
        }
    }
    return mult;
}

// --------------------------------------operator* (with int)------------------------------------------
// operator* to deal when the rhs is int type (non-object)
// post: multiplying polynomial object to the integer right hand side
Poly Poly::operator*(int x) {
    for (int i = 0; i < this->itemCount; i++) {
        this->headPtr[i] *= x;
    }
    return *this;
}

// ------------------------------------------operator+=------------------------------------------------
// uses + operator from previous function
// post: perform the += on two polynomial, return the addition result
Poly Poly::operator+=(const Poly& pol) {
    // deref pointers lead to object.
    // use + operator for adding objects
    *this = *this + pol;
    return *this;
}

// ------------------------------------------operator-=------------------------------------------------
// uses - operator from previous function
// post: perform the -= on two polynomial, return the subtraction result
Poly Poly::operator-=(const Poly& pol) {
    *this = *this - pol;
    return *this;
}

// ------------------------------------------operator*=------------------------------------------------
// uses * operator from previous function
// post: perform the *= on two polynomial, return the multiplication result
Poly Poly::operator*=(const Poly& pol) {
    *this = *this * pol;
    return *this;
}

// ------------------------------------------operator==------------------------------------------------
// param is the object to compare that contain a polynomial's coeff in array
// and power as the index of array
// compare the param(rhs) with current object(lhs)
// post: return true if the two polynomials is the same, false otherwise
bool Poly::operator==(const Poly& pol) {
    if (this->itemCount != pol.itemCount) {
        return false;
    }
    for (int i = 0; i < this->itemCount; i++) {
        if (this->headPtr[i] != pol.headPtr[i]) {
            return false;
        }
    }
    return true;
}

// ------------------------------------------operator!=------------------------------------------------
// compare current object (lhs) with the param object (rhs)
// post: return true is two polynomial are different (not equal), true otherwise
bool Poly::operator!=(const Poly& pol) {
    return !(*this == pol);
}

// ------------------------------------------operator=-------------------------------------------------
// assignment operator
// will adjust lhs object value and make it the same as the param object value (rhs)
// post: lhs object will have the same polynomial value as the rhs object
Poly& Poly::operator=(const Poly& pol) {
    if (this->headPtr == pol.headPtr) {
        return *this;
    }
    if (this->itemCount > pol.itemCount) {
        for (int i = 0; i < this->itemCount; i++) {
            this->headPtr[i] = 0;
        }
        for (int i = 0; i < pol.itemCount; i++) {
            this->headPtr[i] = pol.headPtr[i];
        }
    }
    if (pol.itemCount > this->itemCount) {
        // delete current object info directly to prevent heap corruption.
        // because the current object (lhs) is too short, when assigning with the rhs object directly
        // it access the index that is not valid (bigger than this->itemCount)
        // --> lead to heap corruption
        // delete current object value and pointer completely
        // then perform copying process directly
        delete[] this->headPtr;
        headPtr = nullptr;
        this->itemCount = pol.itemCount;
        this->headPtr = new int[this->itemCount];
        for (int i = 0; i < this->itemCount; i++) {
            this->headPtr[i] = pol.headPtr[i];
        }
    }
    if (this->itemCount == pol.itemCount) {
        for (int i = 0; i < this->itemCount; i++) {
            this->headPtr[i] = pol.headPtr[i];
        }
    }
    // return current modified polynomial.
    return *this;
}

// ------------------------------------------destructor------------------------------------------------
// Destructor (virtual in .h)
// post: destroy all value in the array and set the array pointer to nullptr
Poly::~Poly() {
    // delete the whole array
    delete[] headPtr;
    // set it point to nullptr (good practice)
    headPtr = nullptr;
}