/*	问题描述
	查找满足条件的三数组合：给定一个乱序的整数组A，要求计算所有满足a <= A[i] + A[j] + A[k] <= b的{i, j, k}组合的个数；
	一个数不能被重复使用，即:{i, j, k}组合中的i，j，k互不相等；
	*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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

int main(){
	long total = 0;
	int length = 0, max = 0, min = 0;
	scanf("%d %d %d", &length, &min, &max );
	int *A = new int[length];
	for( int i = 0; i <= length-1; i++ ){
		scanf("%d",A+i);
	}//Init All
	quickSort(A,0,length-1);//quickSort
	//for( int i = 0; i <= length-1; i++ )printf("%d ",*(A+i));
	/*int k1 = 0, k2 = 0;
	for( int i = 0; i <= length - 3; i++ ){
		for( int j = i+1; j <= length -2 ;	j++ ){
			if( A[i]+A[j]+A[j+1] > max || A[i]+A[j]+A[length-1] < min ){
				//printf("%d %d %d %d can't\n",i,j,A[i]+A[j]+A[j+1],A[i]+A[j]+A[length-1]);
				continue;
			}
			//printf("i:%d j:%d ",i,j);
			k1 = bioSearch(A, j+1, length, min-A[i]-A[j]);
			k2 = bioSearch(A, j+1, length, max-A[i]-A[j]);
			k1 = (A[k1] == min-A[i]-A[j]) ? k1 : k1+1;
			if( k1 <= j ) k1 = j+1;
			//printf("k1:%d k2:%d \n",k1,k2);
			if(k1 == length-1){
				if( A[k1]+A[i]+A[j] == min )total++;
				continue;
			}

			if( k2 >= k1 ) total += (k2-k1+1);
			else total+=0;
		}

	}
	printf("%d\n",total);
	*/
	int x = -5;
	//while(x<10){printf("%d \n", bioSearch(A,0,length,x++));}
	getchar();
	getchar();
	getchar();
	return 0;
}


