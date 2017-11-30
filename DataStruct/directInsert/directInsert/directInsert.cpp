#include <iostream>
using namespace std;
void exch(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void directInsert(int* a, int size){
	int temp = a[0], tag = 0;
	for( int i = 0; i <= size-1; i++ ){
		if( a[i] < temp ){
			tag = i;
			temp = a[i];
		}
	}
	a[tag] = a[0];
	a[0] = temp;
	//Make the 1st number is smallest

	for( int i = 0; i <= size-1; i++ )cout<< a[i] << " ";
	cout<<endl;
	//print to see every step

	for( int i = 2; i <= size-1; i++ ){
		temp = a[i];
		int j = i;
		while( a[j] < a[j-1] ){
			exch(a+j, a+j-1);
			j--;
		}
		for(int k = 0; k <= size-1; k++ )
			cout<<a[k]<<" ";
		cout<<endl;
	}
}//directInsertSort

int partition(int *a, int left, int right){
		
}

void quickSort(int* a, int left, int right){
	if( right < left )return;
	int pos = partition(a, left, right);
	quickSort(a, left, pos-1);
	quickSort(a,pos,right);
}


int main(){
	int a[10] = {503,87,512,61,908,170,897,275,653,426};
	directInsert(a,10);
	getchar();
}
