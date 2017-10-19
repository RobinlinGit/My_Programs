#include <iostream>
using namespace std;
void  mat2plus(int mat1[2][2],int mat2[2][2],int mat_re[2][2])
{

	mat_re[0][0] = mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0];
	mat_re[0][1] = mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1];
	mat_re[1][0] = mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0];
	mat_re[1][1] = mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1];

}

void mat_mode(int mat[2][2], int  p)
{
	mat[0][0] = mat[0][0] % p;
	mat[0][1] = mat[0][1] % p;
	mat[1][0] = mat[1][0] % p;
	mat[1][1] = mat[1][1] % p;

}

void equal(int mat[2][2], int mat_re[2][2])
{
	for( int i = 0; i <= 1; i++)
				for ( int j = 0; j <= 1; j++)
				mat[i][j] = mat_re[i][j];
}

int main()
{
	const int p = 9973;
	int basic_mat[2][2]={
		1, 1,
		1, 0
	};

	int n=0;
	int a[20];
	for( int i = 0; i <= 19; i++)
		a[i]=0;

	cin>>n;
	for( int i = 0; i <= n-1; i++)
		cin>>a[i];

	int time = 0;
	int rest = 0;
	int mat[2][2] = { 1, 1, 1, 0};
	int mat_re[2][2];

	for( int i = 0; i <= n-1; i++)
	{
		time = a[i] / p;
		rest = a[i] % p;
	
		for( int i = 0; i <= time-1; i++)
		{
			mat2plus(mat, mat, mat_re);
			equal(mat,mat_re);
			mat_mode(mat_re, p);
			equal(mat, mat_re);
		}
		for( int i = 0; i <= rest-1; i++)
		{
			mat2plus(mat, basic_mat, mat_re);
			equal(mat,mat_re);
			mat_mode(mat_re, p);
			equal(mat,mat_re);
		}
		cout<<mat[1][0]<<endl;

	}
	return 0;
}

	