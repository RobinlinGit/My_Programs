/*	��������
	��������������������ϣ�����һ�������������A��Ҫ�������������a <= A[i] + A[j] + A[k] <= b��{i, j, k}��ϵĸ�����
	һ�������ܱ��ظ�ʹ�ã���:{i, j, k}����е�i��j��k������ȣ�
	*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
using namespace std;
void exchange(int* a, int* b){
	//printf("%d %d\n", *a, *b);
	int temp = *a;
	*a = *b;
	*b = temp;
	//printf("%d %d\n", *a, *b);
}

int partition(int *a, int left, int right){
	int partition = a[right];
	int i = left, j = right-1;
	while(i <= right ){
		while(a[i] <= partition && i < right) i++;
		while(a[j] >= partition && j > left) j--;
		//return to former pos
		if( i >= j )break;
		else exchange(a+i, a+j);//exchange two nums
	}
	exchange(a+i,a+right);
	return i;
}

void quickSort(int *a, int left, int right){
	if( left >= right )return;
	int part = partition(a,left,right);
	quickSort(a,left,part-1);
	quickSort(a,part,right);
}//quickSort 

int bioSearch(int *a, int lo, int hi, int value){//suppose the input legal
	int mi ;
	while( lo < hi ){
		mi = (lo + hi) >> 1;
		if( a[mi] == value )return mi;
		else if( a[mi] > value ) hi = mi;
		else if( a[mi] < value ) lo = mi+1;
	}
	if( a[mi] <= value )
		return mi;
	else return mi-1;
}// return the biggest index which a[find] <= value


void MoveIndexLow(int* A, int i, int j, int &k, int right, int bound){
	while( A[i]+A[j]+A[k-1] >= bound && k-1>j ) k--; // ���k-1�����������ƶ�
}
void MoveIndexHigh(int* A, int i, int j, int &k, int right, int bound){
	while( A[i]+A[j]+A[k] > bound && k>j  ) k--; //�ƶ���С���ڵ�����������Ҳ�����j
}

bool indexRight(int* A, int i, int j, int k1, int k2, int min, int max){
	return ( (A[i]+A[j]+A[k1] >= min) && (A[i]+A[j]+A[k2]<=max) );
}

int main(){
	int length = 0, max = 0, min = 0;
	scanf("%d %d %d", &length, &min, &max );
	int *A = new int[length];
	for( int i = 0; i <= length-1; i++ ){
		scanf("%d",A+i);
	}//Init All
	//for( int i = 0; i <= length-1; i++ )cout<<A[i]<<endl;  
	//getchar();
	quickSort(A,0,length-1);//quickSort
	long long total = 0;
	int minBound = length-1, maxBound = length-1;
	for(int i = 0; i<=length-3; i++){
		minBound = length-1; maxBound = length-1;
		//printf("i:%d\n",i);
		for(int j = i+1; j<=length-2; j++){
			if( minBound>j && maxBound>j ){
				MoveIndexLow(A,i,j,minBound,length-1,min);
				MoveIndexHigh(A,i,j,maxBound,length-1,max);
				if( minBound>j && maxBound>j && indexRight(A,i,j,minBound,maxBound,min,max) )//������index������j����������
					total += maxBound-minBound+1;
				else if( minBound<=j && maxBound>j && (A[i]+A[j]+A[maxBound] <= max) )
					total += maxBound-j;
				else 
					continue;//������һ��ѭ��
			}
			
			else if( minBound<=j && maxBound>j ){
				MoveIndexHigh(A,i,j,maxBound,length-1,max);
				if( maxBound>j ){ 
					if( A[i]+A[j]+A[maxBound] <= max )
						total += maxBound-j;
				}
				else continue;
			}
			else continue;
		}
	}
	printf("%lld\n",total);
	getchar();
	delete[] A;
	getchar();
	return 0;
}
/*
6 10 13
1
2
3
4
5
6
*/
