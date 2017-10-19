#include <cstdio>

struct Node
{
	short row;
	short column;
	int value;
	Node* right;
	Node* down;
	
	
	Node( int m, int n, int v){ row = m; column = n, value = v; right = NULL; down = NULL;}
	Node() { row = -1; column = -1; value = 0; right = NULL; down = NULL; } 
};//Define node struct , it will be used as a basic part of Sparse Matrix

class SparseMatrix{
protected:
	int row;
	int column;
	Node beginNode;

public:
	void addNode(int m, int n, int v );	
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
	SparseMatrix( short m, short n ): row(m), column(n),beginNode() { 
		Node* MatRow = new Node[row];
		Node* MatColumn = new Node[column];
		beginNode.down = MatRow;
		beginNode.right  = MatColumn;
		//create the Node List
	}

	~SparseMatrix(){
		//printf("Îö¹¹º¯Êý\n");
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

	SparseMatrix operator = ( SparseMatrix& A ){ SparseMatrix NewOne = SparseMatrix(A); return NewOne;}
	void delZero();

};
