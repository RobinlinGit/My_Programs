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
	void swapNode(Node* thisNode, int target);
	double* Sedail(double* b);
	double Resf(double* b, double* x);
	SparseMatrix operator = ( SparseMatrix& A ){ SparseMatrix NewOne = SparseMatrix(A); return NewOne;}
	void delZero();

};
