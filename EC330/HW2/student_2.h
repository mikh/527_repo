#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iterator>

using namespace std;

#define DEBUG_MODE

template <typename T>
class student{
public:
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
		self_type operator--() { self_type i = *this; ptr_--; return i;}
		self_type operator++(int junk) { ptr_++; return *this;}
		self_type operator--(int junk) { ptr_--; return *this;}
		reference operator*() { return *ptr_; }
		pointer operator->(){ return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};

	typedef std::reverse_iterator<iterator> reverse_iterator;
	student();
	~student();
	void push_back(T value);
	void insert(iterator position, T value);
	void insert(iterator position, int size, T value);
	T pop_back();
	int size();
	iterator begin(){ return iterator(array); }
	iterator end(){ return iterator(&array[index_head]); }
	reverse_iterator rbegin() { return reverse_iterator(array); }
	reverse_iterator rend() { return reverse_iterator(&array[index_head]); }



private:

	T *array;
	int index_head;
	int max_size;
	const static int BASE_SIZE = 1000;
};

template <typename T>
student<T>::student(){
	#ifdef DEBUG_MODE
		cout<<"constructor"<<endl;
	#endif
	array = new T[BASE_SIZE];
	index_head = 0;
	max_size = BASE_SIZE;
}

template <typename T>
student<T>::~student(){
	#ifdef DEBUG_MODE
		cout<<"destructor"<<endl;
	#endif
	delete[] array;
	array = NULL;
}

template <typename T>
void student<T>::push_back(T value){
	#ifdef DEBUG_MODE
		cout<<"push_back"<<endl;
	#endif
	array[index_head++] = value;
	#ifdef DEBUG_MODE
		if(index_head == max_size)
			cout<<"too big"<<endl;
	#endif
}


template <typename T>
void student<T>::insert(iterator position, T value){
	#ifdef DEBUG_MODE
		cout<<"insert one"<<endl;
	#endif
	index_head++;
	if(index_head == max_size){
		cout<<"too big"<<endl;
	}
	T previous = value;
	for(; position != end(); position++){
		T cur_value = *position;
		*position = previous;
		previous = cur_value;
	}
	*position = previous;

}

template <typename T>
void student<T>::insert(iterator position, int size, T value){
	#ifdef DEBUG_MODE
		cout<<"insert many"<<endl;
	#endif
	for(int ii = 0; ii < size; ii++){
		insert(position, value);
	}
}

template <typename T>
T student<T>::pop_back(){
	#ifdef DEBUG_MODE
		cout<<"pop_back"<<endl;
	#endif
	return array[--index_head];
}

template <typename T>
int student<T>::size(){
	return index_head;
}


#endif
