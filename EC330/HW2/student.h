
#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <iterator>

using namespace std;



template <typename T>
class student{
public:
	
	//iterator 
	class iterator{
		public:
			typedef iterator self_type;
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef forward_iterator_tag iterator_category;
			typedef int difference_type;
			iterator(pointer ptr) : ptr_(ptr){}
			self_type operator++() { self_type i = *this; ptr_++; return i;}
			self_type operator++(int junk) { ptr_++; return *this;}
			reference operator*() { return *ptr_; }
			pointer operator->() { return ptr_; }
			bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
			bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
		private:
			pointer ptr_;
	};
	student();
	void push_back(T value);
	void insert(iterator position, T value);
private:
	T *array;
	int index_head;
	int max_size;
	const static int BASE_SIZE = 10;
};

/*
template <typename PointerType>
class student_iterator{

};*/

template <typename T>
student<T>::student(){
	array = new T[BASE_SIZE];
	index_head = 0;
	max_size = BASE_SIZE;
}

template <typename T>
void student<T>::push_back(T value){
	if(index_head+1 < max_size)
		array[index_head++] = value;
	else{
		//reallocation	-	malloc would be potentially more efficient if we used realloc, but that's not very c++
		T *new_array = new T[max_size*2];
		max_size *= 2;
		for(int ii = 0; ii < index_head; ii++){
			new_array[ii] = array[ii];
		}
		new_array[index_head++] = value;
		delete[] array;
		array = new_array;	//reassign pointer
	}
}


template <typename T>
void student<T>::insert(iterator position, T value){
	if()
}

#endif



