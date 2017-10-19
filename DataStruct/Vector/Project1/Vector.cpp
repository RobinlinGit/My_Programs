/*
This file is about details of the class Vector
Started on 10.07.2017
*/

#include "Vector.h"

//first part is about disordered vector

template <typename T>
void Vector<T>::copyFrom( T const* A, Rank lo, Rank hi ){
	element = new T [Capacity = 2*(hi-lo)];
	while( lo < hi )
		element[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand(){
	if( 2*_size < Capacity ) return;
	if( Capacity < Normal_Capacity ) Capacity = Normal_Capacity;
	Capacity *= 2;
	T* elem = new T[Capacity];
	T* oldElem = element;
	

}