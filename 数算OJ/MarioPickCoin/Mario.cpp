#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int findMax(short* Yizhan, int size, int m ){
	int **find = new int*[m+1];
	int **count = new int*[m+1];
	for(int i = 0; i <= m; i++){
		find[i] = new int[size]();
		count[i] = new int[size]();
	}//给两个数组初始化
	int result =0; //存结果的
	int resultCount = 0;
	int lastRowMax = 0;//上一行的最大值，随时更新
	int lastCount = 0;

	/*for(int i = 0; i <= size-1; i++){
			count[0][i] = 0;
			find[0][i] = 0;
	}	//0子段自然无值
	*/
	find[1][0] = Yizhan[0];  
	count[1][0] = 1;//包含一个字段的时候
	
	for(int i = 1; i <= m; i++){
		if( i > 1 ){
			find[i][i-1] = find[i-1][i-2] + Yizhan[i-1];
			count[i][i-1] = count[i-1][i-2] + 1;
			lastRowMax = (find[i-1][i-1] >= find[i-1][i-2]) ? find[i-1][i-1] : find[i-1][i-2];
			lastCount = (find[i-1][i-1] >= find[i-1][i-2]) ? count[i-1][i-1] : count[i-1][i-2];
		}
		else if( i == 1 ){}//do nothing
		if(i == m) {
			result = find[i][i-1];
			resultCount = m;
		}//如果到m行

		for(int j = i; j <= size-1; j++){
			find[i][j] = (find[i][j-1] >= lastRowMax) ? find[i][j-1] + Yizhan[j] : lastRowMax + Yizhan[j];
			count[i][j] = (find[i][j-1] >= lastCount) ? count[i][j-1] + 1 : lastCount + 1;
			//动态规划
			lastCount = (lastRowMax >= find[i-1][j]) ? lastCount : count[i-1][j];
			lastRowMax = (lastRowMax >= find[i-1][j]) ? lastRowMax : find[i-1][j];
			if( i == m ){
				if( count[i][j] >= m ){
					//printf("%d %d %d %d\n", result,resultCount,i,j);
					resultCount = (result >= find[i][j]) ? resultCount : count[i][j];
					result = (result >= find[i][j]) ? result : find[i][j];
				}
			}
		}
	}
	
	/*printf("result %d resultCount %d\n",result,resultCount);
	if( resultCount < m ){
		int res = find[m][m-1];
		printf("****************************\n");
		for(int i = m-1; i <= size-1; i++){
			if( count[m][i] < m )continue;
			else {
				if( res < find[m][i] )
					res = find[m][i];
			}
		}
		result = res;
	}
	
	printf("result %d resultCount %d\n",result,resultCount);
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= size-1; j++)
			printf("%d ",find[i][j]);
		printf("\n");
	}
	printf("count\n");
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= size-1; j++)
			printf("%d ",count[i][j]);
		printf("\n");
	}
	*/
	for(int i = 0; i <= m; i++){
		delete[] find[i];
		delete[] count[i];
		//printf("删除\n");
	}
	
	delete[] count,find;
	return result;
}

int findMin(short* Yizhan, int size, int m ){
	int **find = new int*[m+1];
	int **count = new int*[m+1];
	for(int i = 0; i <= m; i++){
		find[i] = new int[size]();
		count[i] = new int[size]();
	}//给两个数组初始化
	int lastRowMin = 0;//上一行的最大值，随时更新
	int lastCount = 0;
	/*for(int i = 0; i <= size-1; i++){
			count[0][i] = 0;
			find[0][i] = 0;
	}	//0子段自然无值
	*/
	find[1][0] = Yizhan[0];  
	count[1][0] = 1;//包含一个字段的时候
	int result =100000; //存结果的
	int resultCount = size+1;
	
	for(int i = 1; i <= m; i++){
		if( i != 1 ){
			find[i][i-1] = find[i-1][i-2] + Yizhan[i-1];
			count[i][i-1] = count[i-1][i-2] + 1;
			lastRowMin = (find[i-1][i-1] < find[i-1][i-2]) ? find[i-1][i-1] : find[i-1][i-2];
			lastCount = (find[i-1][i-1] < find[i-1][i-2]) ? count[i-1][i-1] : count[i-1][i-2];
		}
		else if( i == 1 ){} // do nothing
		
		for( int  j = i; j <= size-1; j++){
			find[i][j] = (find[i][j-1] <= lastRowMin) ? find[i][j-1]+Yizhan[j] : lastRowMin+Yizhan[j];
			count[i][j] = (find[i][j-1] <= lastRowMin) ? count[i][j-1]+1 : lastCount+1;
			lastCount = (lastRowMin <= find[i-1][j]) ? lastCount : count[i-1][j];
			lastRowMin = (lastRowMin <= find[i-1][j]) ? lastRowMin : find[i-1][j];
			if( i == m ){
				if( count[i][j] <= size-m )
					if(result >= find[i][j]){
						result = find[i][j];
						resultCount = count[i][j];
					}//含元素个数小于size-m的点， 且值要小
			}
		}
	}



	/*for(int i = 0; i <= m; i++){
		for(int j = 0; j <= size-1; j++)
			printf("%d ",find[i][j]);
		printf("\n");
	}
	printf("count\n");
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= size-1; j++)
			printf("%d ",count[i][j]);
		printf("\n");
	}
	*/
	for(int i = 0; i <= m; i++){
		//printf("删除\n");
		delete[] find[i];
		delete[] count[i];
	}
	delete[] count;
	delete[] find;
	return result;
}
int main(){
	int n = 0; 
	scanf("%d",&n);
	int m = 3;
	long count = 0;
	short *Yizhan = new short[n+1];
	for(int i = 0; i <= n-1; i++){
		scanf("%d",Yizhan+i);
		count += *(Yizhan+i);
	}

	int max = 0, min = 0;
	max = findMax(Yizhan,n,m);
	min = findMin(Yizhan,n,m);
	//printf("%d %d\n",min,count);
	max = (max >= count-min) ? max : count - min;
	printf("%d\n",max);
	delete[] Yizhan;
	return 0;
}

/*
10
1
2
-4
5
6
-9
10
-22
-100
1


10
-1
-2
-3
-4
100
-5
-6
-7
-8
-9
*/