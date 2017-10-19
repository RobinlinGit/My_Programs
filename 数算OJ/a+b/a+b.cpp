//高精度加法
	#include <iostream>
	using namespace std;
	int main()
	{
		char a_[200],b_[200];
		cin>>a_>>b_;

		int a[200],b[200],c[201];
		for (int i=0;i<=199;i++)
		{
			a[i]=0;
			b[i]=0;
			c[i]=0;
		}
		c[200]=0;

		for( int i = 0; i <= strlen(a_)-1; i++)
			a[i] = a_[strlen(a_)-1-i] - '0';
		for( int i = 0; i <= strlen(b_)-1; i++)
			b[i] = b_[strlen(b_)-1-i] - '0';
		int max = (strlen(a_)>=strlen(b_)) ? strlen(a_)-1 : strlen(b_)-1;
		for( int i = 0; i <= max ; i++)
		{
			c[i+1] += ( c[i] + a[i] + b[i]) / 10;
			c[i] = ( c[i] + a[i] + b[i]) % 10;
		
		}

	
		if (c[max+1] != 0) max++;

		for ( int i = max; i >= 0; i--)
			cout<<c[i];
		getchar();

		return 0;
	}

	
