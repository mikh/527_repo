template <typename T>
bigNumT<T>& bigNumT<T>::operator+(bigNumT<T>& addend) {
    bigNumT<T> first, second; 
    bigNumT<T> *result = new bigNumT<T>();  //assume enough space is allocated initially, O(n)

    if (digits.size() > addend.digits.size()) { //assuming most recent version of C++, this is O(1), older versions of the compiler may take up to O(n)
                                                 
        first = addend;
        second = *this;
    } else {
        first = *this;
        second = addend;
    }

    int ii;
    int carry = 0;
    typename T::iterator first_ii = first.digits.begin();  // O(1)
    typename T::iterator second_ii = second.digits.begin(); //O(1)
    for (; first_ii != first.digits.end(); first_ii++, second_ii++) {   //O(n)
        int sum = *first_ii + *second_ii;                   //O(1)
        result->digits.push_back((sum + carry) % base);     //O(1)
        if (sum + carry > (base - 1)) {                     //O(1)
            carry = 1;
        } else {
            carry = 0;
        }
    }

    for (; second_ii != second.digits.end(); second_ii++)   //O(1) since this loop does not run
        if (carry) {
            int dig = (*second_ii + carry);
            result->digits.push_back(dig % base);
            carry = (dig > (base - 1) ? dig / base : 0);
        } else
            result->digits.push_back(*second_ii);
    if (carry)  //O(1)
        result->digits.push_back(carry);

    return *result;
}

//Total: O(n)