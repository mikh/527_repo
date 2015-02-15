#ifndef BIGNUMWITHMINUS
#define BIGNUMWITHMINUS


#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "bigNumT.h"
using namespace std;


template <typename STORAGE = vector<int> > // STORAGE is the class that is used to store digits
class bigNumTwithMinus : bigNumT{
public:
    
    /**
     * @param addend is an initialized bigNumT
     * @return the sum of this number and <addend>
     */
    bigNumTwithMinus& operator-(bigNumTwithMinus<STORAGE>& addend);    
private:
    const static int base = 10; // the base of the number
};




template <typename T>
bigNumTwithMinus<T>& bigNumTwithMinus<T>::operator-(bigNumTwithMinus<T>& addend) {
    bigNumTwithMinus<T> first, second; // second always has at least as many digits as first
    bigNumTwithMinus<T> *result = new bigNumTwithMinus<T>();

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
        int dif = *second_ii - *first_ii - carry;
        if(dif < 0){
            carry = 1;
            dif += base;
        } else{
            carry = 0;
        }

        result->digits.push_back(dif);
    }

    // continue processing the second number (ran out of digits on first number)
    for (; second_ii != second.digits.end(); second_ii++){
        int dif = *second_ii - carry;
        if(dif < 0){
            carry = 1;
            dif += base;
        } else{
            carry = 0;
        }
        result->digits.push_back(dif);
    }
    //if (carry)
        //since we have assumed the result should be positive or 0, carry should never be positive here

    return *result;
}

#endif