#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void HaarChange( float* array, int lo, int hi ){//左闭右开
	float *tempArray = new float[hi-lo];
	float temp = 0;
	for( int i = 0; i < (hi-lo)/2; i++ )	tempArray[i] = (array[2*i+1] + array[2*i] )/2;
	for( int i = (hi-lo)/2; i < hi - lo; i++ ) tempArray[i] = -( array[2*(i-(hi-lo)/2)] - array[2*(i-(hi-lo)/2)+1] ) / 2;
	//小波变换
	int LO = lo ;
	while( lo < hi ){
		array[ lo ] = tempArray[ lo - LO ];lo++;
		
	}//将得到的区间复制

	delete[] tempArray;
}
long Times2N(int N){int sum = 1; while( N-- > 0 )sum*=2;return sum;}
int main(){
	int L;
	scanf("%d",&L);
	long sum = Times2N(L);
	
	float *array = new float[sum];

	for( long i = 0; i <= sum-1 ; i++ ){
		scanf("%f",array+i);getchar();
	}

	for( int i = 0; i <= L-1; i++ ){
		
		HaarChange(array, 0, Times2N(L-i));
	}

	for( int i = 0; i <= sum-1; i++ ){
		printf("%.4f ", array[i]);
	}
	delete[] array;
	getchar();
	getchar();
	return 0;
}
