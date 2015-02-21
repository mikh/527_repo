
#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <iterator>

using namespace std;

//#define DEBUG_MODE


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
			self_type operator--() { self_type i = *this; ptr_--; return i;}
			self_type operator++(int junk) { ptr_++; return *this;}
			self_type operator--(int junk) { ptr_--; return *this;}
			reference operator*() { return *ptr_; }
			pointer operator->() { return ptr_; }
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
	iterator begin(){return iterator(array);}
	iterator end(){return iterator(&array[index_head]);}
	reverse_iterator rbegin(){return reverse_iterator(array);}
	reverse_iterator rend() {return reverse_iterator(&array[index_head]);}

private:
	T *array;
	int index_head;
	int max_size;
	const static int BASE_SIZE = 10000;
};

/*
template <typename PointerType>
class student_iterator{

};*/

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
}

template <typename T>
void student<T>::push_back(T value){
	#ifdef DEBUG_MODE
	cout<<"pushback"<<endl;
	#endif
	if(index_head+1 < max_size)
		array[index_head++] = value;
	else{
		#ifdef DEBUG_MODE
		cout<<"too big pushback"<<endl;
		#endif
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
	
	#ifdef DEBUG_MODE

	cout<<&position <<endl;
	iterator temp = begin();
	cout<<&temp<<endl;
	cout<<"insert 1"<<endl;
	#endif

	int index = distance(begin(), position);
	#ifdef DEBUG_MODE
	cout<<index<<endl;
	#endif

	if(distance(begin(), end()) + 1 > max_size){
		#ifdef DEBUG_MODE
		cout<<"too big"<<endl;
		#endif
		T *new_array = new T[max_size*2];
		max_size *= 2;
		#ifdef DEBUG_MODE
		cout<<distance(begin(), end())<<endl;
		#endif
		for(int ii = 0; ii < distance(begin(), end()); ii++){
			new_array[ii] = array[ii];
		}
		#ifdef DEBUG_MODE
			cout<<"delete"<<endl;
		#endif
		delete[] array;
		#ifdef DEBUG_MODE
			cout<<"reassign"<<endl;
			#endif
		array = new_array;
	}

	#ifdef DEBUG_MODE
		cout<<distance(begin(), end())-1<<endl;
		cout<<index + 1<<endl;
	#endif
	for(int ii = distance(begin(), end())-1; ii >= index+1;  ii--){
		array[ii+1] = array[ii];
	}
	array[index] = value;
	index_head++;
}

template <typename T>
void student<T>::insert(iterator position, int size, T value){
	#ifdef DEBUG_MODE
	cout<<"insert 2"<<endl;
	#endif
	for(int ii = 0; ii < size; ii++){
		insert(position, value);
	}
}

template <typename T>
T student<T>::pop_back(){
	#ifdef DEBUG_MODE
	cout<<"pop back"<<endl;
	#endif

	return array[index_head--];
}
	
template <typename T>
int student<T>::size(){
	#ifdef DEBUG_MODE
	cout<<"size"<<endl;
	#endif
	return index_head;
}
/*
template <typename T>
student<T>::iterator student<T>::begin(){
	return iterator(array);
}

template <typename T>
iterator student<T>::end(){
	return iterator(&array[index_head]);
}
*/
#endif



