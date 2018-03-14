#include <stdio.h>
void change2Up(double** A,double* b,int* solutionIndex ,int size);
void changeRow(double**A ,int row,int row2, int size);
double* Guass(double** A, int size, double* b);
int findMaxIndex(double** A, int i, int j , int size);
double ResA(double ** A, double* x, double* b,int size);
void Sedail(double **A, double* x, double* b, int size);
const double eps = 0.00001;

double fabs(double x){
	return (x>=0)?x:-x;
}
double ResA(double** A, double* x, double* b, int size){
	double sum = 0;
	double b2 = 0;
	
	for(int j = 0; j <= size-1; j++){
			b2 = 0;
			for(int k = 0; k <= size-1; k++){
				b2+= x[k]*A[j][k];
			}
			sum += (b2-b[j])*(b2-b[j]);
	}

	return sum;

}
double* Guass(double** A,int size, double* b){
	double *x = new double[size], *oriB = new double[size];
	double ** store = new double*[size];
	for( int i = 0; i <= size-1; i++ ){
		store[i] = new double[size];
		oriB[i] = b[i];
	}
	for(int i = 0; i <= size-1; i++)
		for(int j = 0; j <= size-1; j++)
			store[i][j] = A[i][j];
	int* solutionIndex = new int[size];
	for(int i = 0; i <= size-1; i++){
		solutionIndex[i] = i;
		x[i] = 0;
	}
	change2Up(A,b,solutionIndex,size);
	/*
	for(int i = 0; i <= size-1; i++){
		for( int j = 0; j <= size-1; j++ ){
			printf("%lf ",A[i][j]);
		}
		printf("\n");
	}
	*/
	for( int i = size-1; i >= 0; i-- ){
		int index = solutionIndex[i];
		x[index] = b[i];
		for( int j = size-1; j > i; j-- ){
			x[index] -= A[i][j]*x[solutionIndex[j]];
		}
		x[index] = x[index]/A[i][i];
		//printf("test:%lf\n",x[index]);
	}
	int count = 1;
	//printf("test:\n");
	for( int i = 0; i <= size-1; i++){
		double temp = x[solutionIndex[i]];
		x[solutionIndex[i]] = x[i];
		x[i] = temp;
	}
	SedailSuit(A,x,b,size);
	while(ResA(store,x,oriB,size) >= 0.1 && count <= 100 ){
		
		Sedail(store,x,b,size);
		count++;
	}

	return x;
}
void SedailSuit(double ** A, double* x, double* b, int size){
	for(int i = 0; i <= size-1; i++){
		if( fabs(A[i][i]) < eps ){
			bool end = false;
			for(int k = 0; k <= size-1 && !end; k++){
				if( fabs(A[k][i]) > eps ){
					b[i] += b[k];
					for( int j = 0; j <= size-1; j ++){
						A[i][j] += A[k][j];
					}
					end = 1;
				}
			}
		}
	}
}

void Sedail(double** A, double* x, double* b,int size){

	for(int i = 0; i <= size-1; i++){
		x[i] = b[i];
		for( int j = 0; j <= size-1; j++ ){
			x[i] -= A[i][j];
		}
		x[i] /= A[i][i];
	}
}
void change2Up(double** A,double* b,int* solutionIndex ,int size){
	double pivot = 0;
	int row = 0;
	double temp = 0;
	for(int i = 0; i <= size-1; i++){
		pivot = A[i][i];
		if( fabs(pivot) <= eps ){
			row = findMaxIndex(A,i,i,size);
			if( i != row ){
				changeRow(A,i,row,size);

				temp = b[i];
				b[i] = b[row];
				b[row] = temp;
				solutionIndex[i] = row;
				solutionIndex[row] = i;
			}//找到下方最大主元，换行
		}
		pivot = A[i][i];
		for( int j = i+1; j <= size-1; j++ ){
			for(int k = i+1; k <= size-1; k++){
				A[j][k] -= A[i][k]*A[j][i]/A[i][i];
				
			}
			b[j] -= b[i] * A[j][i]/A[i][i];
			A[j][i] = 0;
		}//行相消
	}
}
int findMaxIndex(double** A, int i, int j, int size){
	
	int Index = i;
	for( int k = i+1; k <= size-1; k++ ){
		if( fabs(A[k][j]) >= fabs(A[Index][j]) ){
			Index = k;
		}
	}
	return Index;
}//找到最大主元

void changeRow(double**A ,int row,int row2, int size){
	double  temp = 0;
	for( int i = 0; i <= size-1; i++){
		temp = A[row][i];
		A[row][i] = A[row2][i];
		A[row2][i] = temp;
	}
}

