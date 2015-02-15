template <typename T>
bigNumT<T>& bigNumT<T>::operator+(bigNumT<T>& addend) {
    bigNumT<T> first, second;    //O(1)
    bigNumT<T> *result = new bigNumT<T>();  //construction takes O(n+1) time

    if (digits.size() > addend.digits.size()) { //O(1)
                                                 
        first = addend;     //O(1)  only manipulating pointers
        second = *this;     //O(1)
    } else {
        first = *this;      //O(1)
        second = addend;    //O(1)
    }

    int ii;
    int carry = 0;
    typename T::iterator first_ii = first.digits.begin();   //O(1)
    typename T::iterator second_ii = second.digits.begin(); //O(1)
    for (; first_ii != first.digits.end(); first_ii++, second_ii++) {  //O(n)
        int sum = *first_ii + *second_ii;                   //O(1)
        result->digits.push_back((sum + carry) % base);     //Assuming that allocation is large, then this takes O(1). If vector resizing were to occur, this could take much longer
        if (sum + carry > (base - 1)) {                    //O(1)
            carry = 1;
        } else {
            carry = 0;
        }
    }

    for (; second_ii != second.digits.end(); second_ii++)   //since both numbers are n digits long, this loop does not actually run, so O(1)
        if (carry) {
            int dig = (*second_ii + carry);
            result->digits.push_back(dig % base);
            carry = (dig > (base - 1) ? dig / base : 0);
        } else
            result->digits.push_back(*second_ii);
    if (carry)  //O(1)
        result->digits.push_back(carry); //O(1)

    return *result;
}


//Total: O(n) + O(n)*O(1) + O(1) = O(n)