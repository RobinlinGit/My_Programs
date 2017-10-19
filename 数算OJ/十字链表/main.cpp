#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CrossList.h"
using namespace std;
int main(){
	
	int row = 0, column = 0, sum = 0, value = 0;
	scanf("%d %d %d/n",&row,&column,&sum);
	getchar();
	SparseMatrix* NewOne = new SparseMatrix( row, column );
	for( int i = 0; i <= sum-1; i++ ){
		scanf("%d %d %d/n",&row,&column,&value);
		getchar();
		NewOne->addNode( row, column, value );
	}

	SparseMatrix* tranOne = NewOne->transpose();tranOne->showMatrix();
	SparseMatrix* plusOne = NewOne->plus(*tranOne);plusOne->showMatrix();
	SparseMatrix* multOne = NewOne->multiply(*tranOne);multOne->showMatrix();
	
	delete NewOne;
	delete tranOne;
	delete multOne;
	delete plusOne;
	getchar();
	return 0;
}
