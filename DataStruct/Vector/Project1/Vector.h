/*
This header file is just a practice of learning Course Data Structure 
This file is about the linear structure Vector 
Mainly learn from Dr.Deng's book
Date: 10.07.2017
*/

typedef int Rank;	
#define Normal_Capacity 5

template <typename T> class Vector {
protected:
	Rank _size; 
	int Capacity;
	T* element;
	
	void copyFrom( T const* A, Rank lo, Rank hi );
	void expand();
	void shrink();
	bool bubble( Rank lo, Rank hi );
	void bubbleSort( Rank lo, Rank hi );
	Rank max( Rank lo, Rank hi );
	void selectSort( Rank lo, Rank hi );
	void merge( Rank lo, Rank mi, Rank hi );
	void mergeSort( Rank lo, Rank hi );
	Rank partition( Rank lo, Rank hi );
	void quickSort( Rank lo, Rank hi );
	void heapSort( Rank lo, Rank hi );

public:
	Vector( int c = Normal_Capacity, int s = 0, T v = 0 ){
		element = new T[Capacity = c];	for ( _size = 0; _size < s && _szie < Capacity-1 ; element[_size++] = v ); }
	// Need some rubust , all the elements are set as v
	Vector( T const* A, Rank n )	{ copyFrom( A, 0, n );}
	Vector( T const* A, Rank lo, Rank hi )	{ copyFrom( A, lo, hi ); }
	Vector( Vector<T> const& V ) { copyFrom( V.element, 0, V._size ); }	
	Vector( Vector<T> const& V, Rank lo, Rank hi )	{ copyForm( V.element, lo, hi ); }
	//copy Struction function

	~Vector()	{ delete[] element; }

	Rank size() const { return _size; }
	bool empty() const	{ return !_size; }
	int disordered() const;
	Rank find( T const& e ) const { return find( e, 0, _size ); }
	Rank find( T const& e, Rank lo, Rank hi ) const;
	Rank search( T const& e, Rank lo, Rank hi ) const;
	Rank search( T const& e ) { return 0>=_size? -1 : search( T, 0, _size ); }
	//Some API only for read

	T& operator[] ( Rank r ) { return element[r]; }
	Vector<T>& operator = ( Vector<T> const& );
	T remove( Rank r );
	int remove( Rank lo, Rank hi );
	Rank insert( T const& e, Rank r );
	Rank insert( T const& e ) { return insert( e, _size ); }
	void sort( Rank lo, Rank hi );
	void sort() { sort( 0, _size ); }
	void unsort( Rank lo, Rank hi );
	void unsort() { unsort( 0 ,_size ); }
	int deduplicate();	//无序去重
	int uniquify();	//有序去重
	//Some operate API

	void traverse( void (*) (T&) ) ;
	template <typename VST> void traverse( VST& );
	//tanverse using function point
};
//Vector declaration done;








