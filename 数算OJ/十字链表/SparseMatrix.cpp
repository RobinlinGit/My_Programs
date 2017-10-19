#include "CrossList.h";

void SparseMatrix::addNode( int m, int n, int v ){
	if( v == 0 )return;
	Node* left = beginNode.down + m;
	Node* up   = beginNode.right + n;
	//Node* node = new Node( m, n, v );

	while( left->right != NULL && left->right->column <= n )	left = left->right;
	while( up->down!= NULL && up->down->row <= m )	up = up->down;
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
	for( int i = 0; i <= row-1; i++ ){
		Node* temp = (beginNode.down+i)->right;
		while( temp != NULL ){
			printf("%d %d %d\n", temp->row, temp->column, temp->value );
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
			if(temp2->value == 0){
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



