/* 
 * File:   bigNumT.h
 * Author: Prof. Ari Trachtenberg
 * Templated library for arbitrary-precision integer arithmetic
 *
 * Created on February 7, 2015, 9:03 PM
 */

#ifndef BIGNUMT_H
#define	BIGNUMT_H

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

template <typename STORAGE = vector<int> > // STORAGE is the class that is used to store digits
class bigNumT {
    // a class to represent arbitrarily large positive numbers

public:

    /**
     * Constructs a bigNumT with contents equal to the numeric value of <num> base <base>
     * @requires num contains only characters 0-9 and represents a positive integer > 0
     *        or num is omitted, producing a construction of 0
     */
    bigNumT(string num = "");

/**
 * Makes this number be a copy of <otherNum>
 * @param otherNum An initialized bigNumT to copy
 * @return the copied bigNumT
 * 
 */   
    bigNumT& operator=(const bigNumT<STORAGE>& otherNum);

    /**
     * @param addend is an initialized bigNumT
     * @return the sum of this number and <addend>
     */
    bigNumT& operator+(bigNumT<STORAGE>& addend);

/**
 * @param cc An integer > 0
 * @return the product of this number and <cc>
 */
    bigNumT& operator*(int cc);

/**
 * 
 * @param multiplicand is an initialized bigNumT
 * @return the product of this number and <multiplicand>
 */
    bigNumT& operator*(bigNumT<STORAGE>& multiplicand);
 

    /**
     * @param divisor is an initialized bigNumT
     * @return the division of this number by <divisor>
     */
    bigNumT& operator/(bigNumT<STORAGE>& divisor);

/**
 * @param otherNum is an initialized bigNum
 * @return true iff this bigNumT is exactly equal to <otherNum>
 */
    bool operator==(bigNumT<STORAGE>& otherNum);
 
/**
 * 
 * @param otherNum is an initialized bigNum
 * @return true iff this number is <= <otherNum>
 */
    bool operator<=(bigNumT<STORAGE>& otherNum);

    /**
     * @return a human-readable string representing this number
     */
    string print();

protected:
    STORAGE digits; // stores the digits of the current number

private:
    const static int base = 10; // the base of the number
    
    /**
     * Shifts the current number by <cc> digits to the left
     * (equivalent to multiplying by base^<cc>)
     * @param cc An integer >=0
     * 
     */
    void operator<<(int cc);
    
     /**
     * Compares me to <otherNum>.
      * @return -1 if I am smaller than otherNum
      * @return 0 if I am equal to otherNum
      * @return 1 if I am greater than otherNum
     */
    int compare(bigNumT<STORAGE>& otherNum);
};

// IMPLEMENTATION of bigNumT.h

template <typename T>
bigNumT<T>::bigNumT(string num) {
    bool leading = true; // used to ignore leading zeroes
    for (int ii = 0; ii < num.length(); ii++)
        if (leading && num[ii] == '0')
            continue;
        else {
            leading = false;
            digits.insert(digits.begin(), num[ii] - '0');
        }
}

template <typename T>
bigNumT<T>& bigNumT<T>::operator=(const bigNumT<T>& otherNum) {
    digits = otherNum.digits; // simply copy the storage
    return *this;
}

template <typename T>
bigNumT<T>& bigNumT<T>::operator+(bigNumT<T>& addend) {
    bigNumT<T> first, second; // second always has at least as many digits as first
    bigNumT<T> *result = new bigNumT<T>();

    if (digits.size() > addend.digits.size()) { /* assign first and second so that second always has
                                                 ** at least as many digits as first. */
        first = addend;
        second = *this;
    } else {
        first = *this;
        second = addend;
    }

    int ii;
    int carry = 0;
    typename T::iterator first_ii = first.digits.begin();   // first_ii = digits[ii], the ii-th digit of <first>
    typename T::iterator second_ii = second.digits.begin(); // second_ii = second.digits[ii], the ii-th digit of <second>
    for (; first_ii != first.digits.end(); first_ii++, second_ii++) {
        int sum = *first_ii + *second_ii;                   // add the ii-th digits
        result->digits.push_back((sum + carry) % base);
        if (sum + carry > (base - 1)) {                     // check for carry
            carry = 1;
        } else {
            carry = 0;
        }
    }

    // continue processing the second number (ran out of digits on first number)
    for (; second_ii != second.digits.end(); second_ii++)
        if (carry) {
            int dig = (*second_ii + carry);
            result->digits.push_back(dig % base);
            carry = (dig > (base - 1) ? dig / base : 0);
        } else
            result->digits.push_back(*second_ii);
    if (carry)
        result->digits.push_back(carry);

    return *result;
}

template <typename T>
bigNumT<T> &bigNumT<T>::operator*(int cc) {
    // multiplies by small integer cc
    int carry = 0;
    bigNumT<T> *result = new bigNumT<T>();

    typename T::iterator ii = digits.begin();
    for (; ii != digits.end(); ii++) {
        long prod = (*ii) * cc + carry;
        result->digits.push_back(prod % base);
        if (prod > (base - 1))
            carry = prod / base;
        else
            carry = 0;
    }

    while (carry) {
        result->digits.push_back(carry % base);
        carry /= base;
    }

    return *result;
}

template <typename T>
bigNumT<T> &bigNumT<T>::operator*(bigNumT<T>& multiplicand) {
    // multiplies me by each digit of multiplicand (shifting accordingly), and returns the sum.
    // effectively implements long multiplication.
    bigNumT<T> *sum = new bigNumT<T>();  // sum = 0

    int ii = 0;
    typename T::iterator multi_ii = multiplicand.digits.begin();       // multi_ii = multiplicand[ii], the ii-th digit of multiplicand
    for (; multi_ii != multiplicand.digits.end(); multi_ii++, ii++) {
        bigNumT<T> smallProd = *this * (int) *multi_ii;                // multiplies me by the ii-th digit of multiplicand
        smallProd << ii;                                               // shift accordingly
        *sum = *sum + smallProd;
    }
    return *sum;
}

template <typename T>
bigNumT<T> &bigNumT<T>::operator/(bigNumT<T>& divisor) {
    /* Division by guessing:  stupid but effective
    ** Guess each digit of the result, from most to least significant.
    **    Start at largest possible value for the digit, and decrease until
    **    the guess * divisor is less than me.
    */  
    bigNumT<T> *guess = new bigNumT<T>("0");
    for (int ii = digits.size() - 1; ii >= 0; ii--) {  // each digit of the result, in turn
        int dig;
        bigNumT<T> trial("");
        bigNumT<T> num("1");
        num << ii;
        for (dig = base - 1; dig > 0; dig--) {         // the current digit being guessed
            trial = (num * dig);
            if ((*guess + trial) * divisor <= *this)   // got a product less than me
                break;
        }
        if (dig != 0)
            *guess = *guess + trial;                   // update my guess

    }

    if (guess->digits.size() == 1 && *(guess->digits.begin()) == 0) // represent [0] as [] for sake of consistency
        guess->digits.pop_back();

    return *guess;
}

template <typename T>
int bigNumT<T>::compare(bigNumT<T>& otherNum) {
     if (digits.size() > otherNum.digits.size())
        return 1;
    if (digits.size() < otherNum.digits.size())
        return -1;

    // same number of digits
    typename T::iterator ii = digits.end(); // reverse iterator; starts at end and goes to front
    typename T::iterator otherNum_ii = otherNum.digits.end();
    for (; ii != digits.begin();) {
        --ii;
        --otherNum_ii;
        if (*ii < *otherNum_ii)
            return -1;
        else if (*ii > *otherNum_ii)
            return 1;
    }
    return 0; // they are equal
}

template <typename T>
bool bigNumT<T>::operator==(bigNumT<T>& otherNum) {
    return compare(otherNum)==0;
}

template <typename T>
bool bigNumT<T>::operator<=(bigNumT<T>& otherNum) {
    return compare(otherNum)<=0;
}

template <typename T>
string bigNumT<T>::print() {
    string tmp = "";
    if (digits.size() == 0) return "[0]";
    typename T::reverse_iterator ii = digits.rbegin();
    for (; ii != digits.rend(); ii++)
        tmp += '0' + *ii;
    return tmp;
}

template <typename T>
void bigNumT<T>::operator<<(int cc) {
    // shifts up by cc powers of ten, cc>=0
    digits.insert(digits.begin(), cc, 0);
}

#endif	/* BIGNUMT_H */

