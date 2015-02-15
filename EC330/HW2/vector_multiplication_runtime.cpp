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