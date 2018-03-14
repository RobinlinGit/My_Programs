#include "CrossList.h";
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const double eps = 0.000001;
double absolute(double x){
	return (x>=0)?x:-x;
}
double dis(double* x, double* y, int n){
	double sum = 0;
	for(int i = 0; i <= n-1; i++)
		sum = (absolute(x[i]-y[i]) >= sum) ? absolute(x[i]-y[i]) : sum;
	return sum;
}
double SparseMatrix::Resf(double* b, double* x){
	double sum = 0;
	for( int i = 0; i <= row-1; i++){
		Node* ithRow = beginNode.down + i;
		ithRow = ithRow->right;
		double y = 0;
		while( ithRow != NULL ){
			y += ithRow->value * x[ithRow->column];
			ithRow = ithRow->right;
		}
		sum += (y-b[i])*(y-b[i]);
	}
	return sum;
}

void SparseMatrix::addNode( int m, int n,double v ){
	if( v == 0 )return;
	Node* left = beginNode.down + m;
	Node* up   = beginNode.right + n;
	//Node* node = new Node( m, n, v );

	while( left->right != NULL ) {
		if( left->right->column <= n )
			left = left->right;
		else break;
	}
	while( up->down!= NULL ) {
		if( up->down->row <= m )	
			up = up->down;
		else break;
	}
	//找到前继
	if( left->column == n )	left->value += v;
	else {
		Node* NewOne = new Node( m, n, v );
		NewOne->right = left->right;
		left->right = NewOne;

		NewOne->down = up->down;
		up->down = NewOne;
	}//如果以前存在此点，即可加值，否则直接加入新点，一次判断即可

}//加点

SparseMatrix::SparseMatrix( SparseMatrix& A ){
	row = A.row; column = A.column;
	Node* MatRow = new Node[row];
	Node* MatColumn = new Node[column];
	beginNode.down = MatRow;
	beginNode.right  = MatColumn;

	for( int i = 0; i <= A.row-1; i++ ){
		Node * temp = (A.beginNode.down+i)->right;
		while( temp != NULL ){
			addNode( temp->row, temp->column, temp->value );
			temp = temp->right;
		}
	}//完成对每个点的复制
}//复制构造函数

void SparseMatrix::showMatrix(){
	printf("begin to show mat\n");
	for( int i = 0; i <= row-1; i++ ){
		Node* temp = (beginNode.down+i)->right;
		while( temp != NULL ){
			printf("%d %d %lf\n", temp->row, temp->column, temp->value );
			temp = temp->right;
		}
	}
}//输出矩阵，还需看OJ的要求修改

SparseMatrix* SparseMatrix::transpose(){
	SparseMatrix* NewOne = new SparseMatrix( column, row );
	Node *temp = NULL;
	for( int i = 0; i <= row-1; i++ ){
		temp = (beginNode.down + i)->right;
		while( temp != NULL ){
			NewOne->addNode( temp->column, temp->row, temp->value );
			temp = temp->right;
		}

	}
 	


	//版本一
	/*Node* temp = NewOne->beginNode.right, *temp2 = NULL;
	NewOne->beginNode.right = NewOne->beginNode.down;
	NewOne->beginNode.down = temp;
	//完成对头部的互换
	

	int tempNum = NewOne->row; NewOne->row = NewOne->column; NewOne->column = tempNum;
	for(int i = 0; i <= row-1; i++ ){
		temp = NewOne->beginNode.down + i;
		while( temp != NULL ){
			temp2 = temp->down;
			temp->down = temp->right;
			temp->right = temp2;
			//指针互换

			tempNum = temp->row;
			temp->row = temp->column;
			temp->column = tempNum;
		
			//对应值互换
			temp = temp2;
		}//对实际矩阵中的所有点右下指针互换，达到转置效果
	}
	for( int j = 0; j <= column-1; j++ ){
		temp = NewOne->beginNode.right+j;
		temp->down = temp->right;
		temp->right = NULL;
	}*/
	return NewOne;
}//转置

SparseMatrix* SparseMatrix::plus( SparseMatrix& B ){
	Node* temp = NULL;
	if( B.column != column || B.row != row ) return NULL;
	SparseMatrix* NewOne = new SparseMatrix( *this );
	for( int i = 0; i <= row-1; i++ ){
		temp = (B.beginNode.down+i)->right;
		while( temp != NULL ){
			NewOne->addNode( temp->row, temp->column, temp->value );
			temp = temp->right;
		}
	}
	NewOne->delZero();
	return NewOne;
}//矩阵加法

SparseMatrix* SparseMatrix::multiply( SparseMatrix& B ){
	Node *temp1 = NULL, *temp2 = NULL;
	if( column != B.row )	return NULL;

	SparseMatrix* NewOne = new SparseMatrix( row, B.column );
	for( int i = 0; i <= row-1; i++ )
		for( int j = 0; j <= B.column-1; j++ ){
			//printf("%d,%d\n",i,j);
			int sum = 0;
			temp1 = (beginNode.down+i)->right;
			temp2 = (B.beginNode.right+j)->down;
			while( temp1 != NULL && temp2 != NULL ){
				if( temp1->column == temp2->row ){
					sum += temp1->value * temp2->value;
					temp1 = temp1->right;
					temp2 = temp2->down;
				}
				else (temp1->column > temp2->row ) ? ( temp2 = temp2->down ) : ( temp1 = temp1->right) ;
			}
			NewOne->addNode( i, j, sum );
		}
		NewOne->delZero();
	return NewOne;
}//矩阵乘法

void SparseMatrix::delZero(){
	for( int i = 0; i <= row-1; i++ ){
		
		Node* temp2 = (beginNode.down+i)->right;
		while( temp2 != NULL ){
			if(absolute(temp2->value) <= eps){
				int m = temp2->row, n = temp2->column;
				Node* left = beginNode.down + m;
				Node* up   = beginNode.right + n;
	
				while( left->right != NULL && left->right->column < n )	left = left->right;
				while( up->down!= NULL && up->down->row < m )	up = up->down;

				up->down = temp2->down;
				left->right = temp2->right;
				delete temp2;
				temp2 = left->right;
			}
			else 
				temp2 = temp2->right;
		}
	}

}
//以前的OJ

void SparseMatrix::SwapRow(int i, int j){
	Node* ithRowHead = beginNode.down + i;
	Node* jthRowHead = beginNode.down + j;
	Node* ithRow = ithRowHead->right;
	Node* jthRow = jthRowHead->right;
	ithRowHead->right = jthRow;
	jthRowHead->right = ithRow;
	//头部互换

	while( ithRow!= NULL && jthRow != NULL ){
		if( ithRow->column == jthRow->column ){
			double temp = ithRow->value;
			ithRow->value = jthRow->value;
			jthRow->value = temp;
			ithRow = ithRow->right;
			jthRow = jthRow->right;
		}//如果两个处于同列

		else {//两个处于不同列
			Node* thisNode = (ithRow->column < jthRow->column) ? ithRow : jthRow;
			int thisIndex = (ithRow->column < jthRow->column) ? i : j;
			int otherIndex = (thisIndex == i) ? j : i;
			swapNode(thisNode, otherIndex);
			if( thisIndex == i )ithRow = ithRow->right;
			else jthRow = jthRow->right;
		}
	}
	while(ithRow != NULL ){
		swapNode(ithRow, j);
		ithRow = ithRow->right;
	}
	while(jthRow != NULL){
		swapNode(jthRow,i);
		jthRow = jthRow->right;
	}
	//对每行元素的行数重新赋值
	while( ithRowHead != NULL ){
		ithRowHead->row = i;
		ithRowHead = ithRowHead->right;
	}
	while( jthRowHead != NULL ){
		jthRowHead->row = j;
		jthRowHead = jthRowHead->right;
	}

}//完成交换
void SparseMatrix::swapNode(Node* thisNode, int j ){
		int thisIndex = thisNode->row;
		int otherIndex = j;
		Node* parentThis = beginNode.right + thisNode->column;
		Node* parentOther = parentThis;
		
		
		while( parentThis->down != NULL && parentThis->down->row < thisIndex ) parentThis = parentThis->down;		
		while( parentOther->down != NULL && parentOther->down->row < otherIndex ) parentOther = parentOther->down;
		if(parentThis->down == thisNode){
		if( thisNode->down != NULL && parentThis->row < otherIndex && otherIndex <= thisNode->down->row ){
					//do nothing
			}
			else if( thisNode->down == NULL && parentThis->row < otherIndex ){}//do nothing ,too
			else {
				Node* childNode = parentOther->down;
				if( parentOther != thisNode && childNode != thisNode && parentThis != thisNode){
					parentThis->down = thisNode->down;
					parentOther->down = thisNode;
					thisNode->down = childNode;
					}
				}//交换指针使得相对位置ok	
		}
}

void SparseMatrix::changeToDownTri(int* solutionIndexArray,double *b){
	for(int i = 0; i <= row-1; i++){
		bool needChangePivot = false;
		Node* pivotNode = beginNode.down + i;
		while( pivotNode->column < i && pivotNode != NULL )
			pivotNode = pivotNode->right;
		if( pivotNode != NULL && pivotNode->right != NULL ){
			if( pivotNode->right->column != i ) //即aii = 0
				needChangePivot = true;
			else pivotNode = pivotNode->right;	
		}
		if(pivotNode->column != i) needChangePivot = true;
		//以上看是否需要换主元

		if(needChangePivot){
			Node* pivotCol = beginNode.right + i;
			while( pivotCol != NULL && pivotCol->row < i ) pivotCol = pivotCol->down;
			int tempRow = pivotCol->row;
			if(pivotCol->down != NULL) pivotCol = pivotCol->down;
			SwapRow(i,pivotCol->row);
			pivotNode = pivotCol;
			//交换向量元素次序
			int temp = solutionIndexArray[i];
			solutionIndexArray[i] = solutionIndexArray[tempRow];
			solutionIndexArray[tempRow] = temp;
			double temp2 = b[i];
			b[i] = b[tempRow];
			b[tempRow] = temp2;
		}//如果需要换主元

		double pivot = pivotNode->value;
		double mulitple = 1;
		Node* ithCol = (beginNode.right + i)->down;
		while(ithCol != NULL){
			if(ithCol->row <= i) {
				if(ithCol != ithCol->down)
					ithCol = ithCol->down;
				else break;
			}
			else {
				mulitple = -ithCol->value / pivot;
				add2Row(mulitple,i,ithCol->row);
				//在Row中实现列的相加
				b[ithCol->row] += mulitple*b[i];
				ithCol = ithCol->down;
			}
		}//消去
		pivotNode->down = NULL;
	}
	for(int i = 0; i <= row-1; i++){
		Node* ithRow = (beginNode.down + i);
		Node* temp = ithRow->right;
		while( temp->column < i ){
			ithRow->right = temp->right;
			delete temp;
			temp = ithRow->right;
		}
	}//to make sure it's upTri

}

double* SparseMatrix::Guass(double* b){
	int* solutionIndex = new int[row];
	for(int i = 0; i <= row-1; i++)
		solutionIndex[i] = i;
	changeToDownTri(solutionIndex,b);//化成上三角矩阵
	double* x = new double[row];
	//showMatrix();
	


	for(int i = row-1; i >= 0; i--){
		Node* ithRow = beginNode.down+i;
		ithRow = ithRow->right;
		double aii = ithRow->value;
		ithRow = ithRow->right;
		x[solutionIndex[i]] = b[i];
		//printf("%d %lf\n",i,x[solutionIndex[i]]);
		while(ithRow != NULL){
			x[solutionIndex[i]] -= x[ithRow->column]*(ithRow->value);
			if( ithRow == ithRow->right ) break;
			ithRow = ithRow->right;
		}
		//printf("%d %lf\n",i,x[solutionIndex[i]]);
		x[solutionIndex[i]] = x[solutionIndex[i]]/aii;
		//printf("%d %lf\n",i,x[solutionIndex[i]]);
	}//向上求解

	return x;

}
void SparseMatrix::add2Row(double mul, int base, int head){//only for Guass, not generally
	Node* baseRow = beginNode.down + base;
	Node* headRow = beginNode.down + head;
	baseRow = baseRow->right;
	headRow = headRow->right;
	while(baseRow != NULL ){
		/*if( baseRow->column > headRow->column ){
			if(headRow->right != NULL){
				if( baseRow->column < headRow->right->column ){
					Node* tempNew = new Node(head, baseRow->column, baseRow->value * mul);
					Node* right = headRow->right;
					headRow->right = tempNew;
					tempNew->right = right;
				}//加入新点
				else if( baseRow->column == headRow->right->column ){
					headRow->right->value += baseRow->value*mul;
				}
				else headRow = headRow->right;
			}
			else {
				Node* tempNew = new Node(head, baseRow->column, mul*baseRow->value);
				headRow->right = temp
			}//突然发现还需要上下指针也要对齐，太麻烦
			*/
		addNode(head,baseRow->column,baseRow->value*mul);
		baseRow = baseRow->right;
	}
}

double* SparseMatrix::Sedail(double* b){
	double *x= new double[row];
	int * solutionIndex = new int[row];
	for(int i = 0; i <= row-1; i++){
		
		x[i] = 1;
		
		solutionIndex[i] = i;
	}
	for( int i = 0; i <= row-1; i++){
		Node* ithRow = beginNode.down + i;
		bool needChange = false;
		while( ithRow != NULL && ithRow->right != NULL && ithRow->right->column < i )
			ithRow = ithRow->right;
		if( ithRow->right == NULL || ithRow->right->column != i ){
			needChange = 1;
		}

		if(needChange){
			Node* ithCol = beginNode.right + i;
			double max = 0;
			while( ithCol != NULL && ithCol->down != NULL && ithCol->row < i )
				ithCol = ithCol->down;
			max = fabs(ithCol->value);
			while( ithCol->down != NULL  ){
				if( fabs(ithCol->value) >= max ){
					max = ithCol->value;
				}
				ithCol = ithCol->down;
			}
			SwapRow(i,ithCol->row);
			solutionIndex[i] = ithCol->row;
			solutionIndex[ithCol->row] = i;
			double temp = b[i];
			b[i] = b[ithCol->row];
			b[ithCol->row] = temp;
		}//每行都有主元
	}
	//showMatrix();

	int count = 0;
	//printf("turn %d",count);

	while( count <= 100 && Resf(b,x) >= 0.1 ){ 
		//printf("turn %d",count);
		for(int i = 0; i <= row-1; i++){
			Node* ithRow = beginNode.down + i;
			while( ithRow->column < i )ithRow = ithRow->right;
			double aii = ithRow->value;
			ithRow = beginNode.down + i;
			x[i] = b[i];
			while( ithRow->right != NULL ){
				if( ithRow->column == i ){
					ithRow = ithRow->right;
					continue;
				}
				else {
					x[i] -= ithRow->value * x[ithRow->column];
					ithRow = ithRow->right;
				}
			}
			x[i] /= aii;
		}
		count++;
	}
	for( int i = 0; i<=row-1; i++)printf("%lf\n",x[solutionIndex[i]]);

	delete[] solutionIndex;
	return x;
}

