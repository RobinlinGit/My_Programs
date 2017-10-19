#include "CrossList.h";

void SparseMatrix::addNode( int m, int n, int v ){
	if( v == 0 )return;
	Node* left = beginNode.down + m;
	Node* up   = beginNode.right + n;
	//Node* node = new Node( m, n, v );

	while( left->right != NULL && left->right->column <= n )	left = left->right;
	while( up->down!= NULL && up->down->row <= m )	up = up->down;
	//�ҵ�ǰ��
	if( left->column == n )	left->value += v;
	else {
		Node* NewOne = new Node( m, n, v );
		NewOne->right = left->right;
		left->right = NewOne;

		NewOne->down = up->down;
		up->down = NewOne;
	}//�����ǰ���ڴ˵㣬���ɼ�ֵ������ֱ�Ӽ����µ㣬һ���жϼ���

}//�ӵ�

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
	}//��ɶ�ÿ����ĸ���
}//���ƹ��캯��

void SparseMatrix::showMatrix(){
	for( int i = 0; i <= row-1; i++ ){
		Node* temp = (beginNode.down+i)->right;
		while( temp != NULL ){
			printf("%d %d %d\n", temp->row, temp->column, temp->value );
			temp = temp->right;
		}
	}
}//������󣬻��迴OJ��Ҫ���޸�

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
 	


	//�汾һ
	/*Node* temp = NewOne->beginNode.right, *temp2 = NULL;
	NewOne->beginNode.right = NewOne->beginNode.down;
	NewOne->beginNode.down = temp;
	//��ɶ�ͷ���Ļ���
	

	int tempNum = NewOne->row; NewOne->row = NewOne->column; NewOne->column = tempNum;
	for(int i = 0; i <= row-1; i++ ){
		temp = NewOne->beginNode.down + i;
		while( temp != NULL ){
			temp2 = temp->down;
			temp->down = temp->right;
			temp->right = temp2;
			//ָ�뻥��

			tempNum = temp->row;
			temp->row = temp->column;
			temp->column = tempNum;
		
			//��Ӧֵ����
			temp = temp2;
		}//��ʵ�ʾ����е����е�����ָ�뻥�����ﵽת��Ч��
	}
	for( int j = 0; j <= column-1; j++ ){
		temp = NewOne->beginNode.right+j;
		temp->down = temp->right;
		temp->right = NULL;
	}*/
	return NewOne;
}//ת��


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
}//����ӷ�

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
}//����˷�

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



