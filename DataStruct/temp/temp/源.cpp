#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

struct Node
{
	int row;
	int column;
	double value;
	Node* right;
	Node* down;
	
	
	Node( int m, int n, double v){ row = m; column = n, value = v; right = NULL; down = NULL;}
	Node() { row = -1; column = -1; value = 0; right = NULL; down = NULL; } 
};//Define node struct , it will be used as a basic part of Sparse Matrix

class SparseMatrix{
protected:
	int row;
	int column;
	Node beginNode;

public:
	void addNode(int m, int n, double v );	
	//add a node in the matrix
	//if the node aredy exists, plus it

	SparseMatrix* transpose();	
	SparseMatrix* plus( SparseMatrix& B );
	SparseMatrix* multiply( SparseMatrix& B );
	//if two can multiply/plus, return the result
	//else return a void matrix
	
	void showMatrix();
	//print the matrix
	

	SparseMatrix( SparseMatrix& );
	SparseMatrix( int m, int n ): row(m), column(n),beginNode() { 
		Node* MatRow = new Node[row];
		Node* MatColumn = new Node[column];
		beginNode.down = MatRow;
		beginNode.right  = MatColumn;
		//create the Node List
	}

	~SparseMatrix(){
		//printf("析构函数\n");
		Node * temp = NULL, *next = NULL;
		delete[] beginNode.right; beginNode.right = NULL;
		for( int i = 0; i < row-1; i++ ){
			temp = (beginNode.down+i)->right;
			while( temp != NULL ){
				next = temp->right;
				delete temp; 
				temp = next;
			}

		}
		delete[] beginNode.down;
		
	}//free the space

	Node* operator[] (int i){
		return beginNode.down + i;
	}//Search by index

	double Item(int i,int j){
		Node* iRow = (*this)[i];
		while( iRow->column < j )
			iRow = iRow->right;
		return (iRow->column == j) ? iRow->value : 0;
	}//find mat(i,j)

	void SwapRow(int i, int j);
	void changeToDownTri(int* solutionIndex, double *b);
	double* Guass(double* b);
	void add2Row(double mul, int baseRow, int headRow);


	SparseMatrix operator = ( SparseMatrix& A ){ SparseMatrix NewOne = SparseMatrix(A); return NewOne;}
	void delZero();

};

const double eps = 0.000001;
double abs(double x){
	return (x>=0)?x:-x;
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
			if(abs(temp2->value) <= eps){
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

void SparseMatrix::SwapRow(int i, int j){
	Node* iRowHead = (*this)[i];
	Node* jRowHead = (*this)[j];
	Node* iNode = iRowHead->right;
	Node* jNode = jRowHead->right;
	
	iRowHead->right = jNode;
	jRowHead->right = iNode;
	//行互换，接下来列互换

	while(iNode != NULL && jNode != NULL){//将列上的元素互换
		if(iNode->column != jNode->column){//两个数组的头指针列不同情况下
			Node* first = (iNode->column > jNode->column) ? jNode : iNode;
			int thisRow = first->row;
			int otherRow = (thisRow==i) ? j : i;
			int Column = first->column;
			Node* firColumn = (beginNode.right) + Column;
			
			Node* upOfFirst = NULL;Node* upOfOther = NULL;
			bool find2Node = false;
			//declare some variaties

			while( firColumn != NULL && !find2Node ){
				if( firColumn->down == NULL ){
					upOfOther = firColumn;
					break;
				}//若出现奇怪情况
				if( firColumn->down->row == thisRow ) upOfFirst = firColumn;
				if( firColumn->row < otherRow && firColumn->down->row >= otherRow )
					upOfOther = firColumn;
				if( upOfFirst != NULL && upOfOther != NULL )find2Node = true; 
				firColumn = firColumn->down;
			}//找到上继

			if( !(upOfFirst->row > otherRow) && !(first->row > upOfOther->row) )
				//此时不做任何处理
				;
			else{
				upOfFirst->down = first->down;
				Node* tempDown = upOfOther->down;
				upOfOther->down = first;
				first->down = tempDown;
			}

			if(iNode->column > jNode->column) jNode = jNode->right;
			else {
				if(iNode->right == NULL)
					iNode = NULL;
				else
					iNode = iNode->right;
			}
		}
		else {//若两列的头部指针列相同
			Node* iRowp = iNode;
			Node* jRowp = jNode;
			if( (iRowp->down != NULL && iRowp->down == jNode) ||
				 jRowp->down != NULL && jRowp->down == iNode)
			{
				double temp = iRowp->value;
				iRowp->value = jRowp->value;
				jRowp->value = temp;
			}//值交换
			else {
				Node* UpOfI = (beginNode.right)+iRowp->column;
				Node* UpOfJ = (beginNode.right)+jRowp->column;
				while( UpOfI->down != iRowp) UpOfI = UpOfI->down;
				while( UpOfJ->down != jRowp) UpOfJ = UpOfJ->down;
				Node* tempDown = jRowp->down;
				jRowp->down = iRowp->down;
				iRowp->down = tempDown;
				UpOfI->down = jRowp;
				UpOfJ->down = iRowp;
			}//一系列指针交换
			jNode = jNode->right;
			iNode = iNode->right;
		}

		iNode = (this->beginNode.down) + j;
		jNode = (this->beginNode.down) + i;
		while(iNode->right != NULL){
			iNode->row = j;
			iNode = iNode->right;
		}
		while(jNode->right != NULL){
			jNode->row = i;
			jNode = jNode->right;
		}
	}
}//完成交换
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
			if(pivotCol->down != NULL) pivotCol = pivotCol->down;
			SwapRow(i,pivotCol->row);
			pivotNode = pivotCol;
			//交换向量元素次序
			int temp = solutionIndexArray[i];
			solutionIndexArray[i] = solutionIndexArray[pivotCol->row];
			solutionIndexArray[pivotCol->row] = temp;
			double temp2 = b[i];
			b[i] = b[pivotCol->row];
			b[pivotCol->row] = temp2;
		}//如果需要换主元

		double pivot = pivotNode->value;
		double mulitple = 1;
		Node* ithCol = (beginNode.right + i)->down;
		while(ithCol != NULL){
			if(ithCol->row <= i) ithCol = ithCol->down;
			else {
				mulitple = -ithCol->value / pivot;
				add2Row(mulitple,i,ithCol->row);
				//在Row中实现列的相加
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

	for(int i = row-1; i >= 0; i--){
		Node* ithRow = beginNode.down+i;
		ithRow = ithRow->right;
		double aii = ithRow->value;
		ithRow = ithRow->right;
		x[solutionIndex[i]] = b[i];
		while(ithRow != NULL){
			x[solutionIndex[i]] -= x[ithRow->column]*(ithRow->value);
			ithRow = ithRow->right;
		}
		x[solutionIndex[i]] = x[solutionIndex[i]]/aii;
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
	}
}




int main(){
	int size = 0, nums = 0;
	scanf("%d %d",&size,&nums);
	SparseMatrix* A = new SparseMatrix(size,size);
	int row = 0, column = 0;
	double value = 0;
	for(int i = 0; i <= nums-1; i++){
		scanf("%d %d %lf",&row,&column,&value);
		A->addNode(row,column,value);
	}
	double* b = new double[size];
	double* x;
	for(int i = 0; i <= size-1; i++){
		scanf("%lf",b+i);
	}
	x = A->Guass(b);
	for(int i = 0; i <= size-1; i++)
		printf("%12.8lf",x[i]);
	getchar();

	delete A;
	delete[] b,x;
	getchar();
	return 0;
}
/*
3 4
0 0 1.00
1 1 2.00
2 2 3.00
1 2 2.4213214
*/