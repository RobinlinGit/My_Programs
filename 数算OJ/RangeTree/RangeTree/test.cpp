#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <stdio.h>
#include "RangeTree.h"
using namespace std;


int main(){
	int m=0, n=0;
	scanf("%d %d", &m, &n);
	searchPoint* B = new searchPoint[n];
	treeNode* A = new treeNode[m];
	for(int i = 0; i < m; i++){
		scanf("%d %d",&(A[i].x),&(A[i].y));
		//getchar();
	}
	for(int i = 0; i < n; i++){
		scanf("%d %d %d",&(B[i].x), &(B[i].y), &(B[i].dis));
		
	}
	
	RangeTree rangeTree(A,m);
	rangeTree.buildTree();
	
	
	vector<int> answer;
	for(int i = 0; i < n; i++){
		answer.insert(answer.end(),rangeTree.BioSearch(B[i]));
	}
	for(int i = 0; i < n; i++){
		printf("%d\n",answer[i]);
	}
	getchar();
	getchar();
	delete[] B;
	return 0;
}
/*
10 1
1 1
2 2
3 3
4 4
5 5
98 97
6 7
78 23
234 0
79 67
*/

