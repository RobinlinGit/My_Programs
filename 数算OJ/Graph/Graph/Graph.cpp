/*����������
	�Ƽ�������ʶ���û���Ҫ�����˻�����ʶ������ʶ����ͬ���˴����3
	����һ������
	���һ�������Ƿ�Ϊ������ʶ��
	�Լ�����ĳ�����û�������ʶ��·��
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

/*˼·��λ����*/
/*ͼ���ڽӾ����ʼ��*/
int** InitGraph(int Size){
	int **Graph = new int*[Size];
	if( Size % 32 != 0){
		for( int i = 0; i <= Size-1; Graph[i] = new int[Size/32+1] , i++);
		for( int i = 0; i <= Size-1; i++ )
			for( int j = 0; j <= Size/32; j++ )
				Graph[i][j] = 0;
	}
	else {
		for( int i = 0; i <= Size-1; Graph[i] = new int[Size/32],i++);
		for( int i = 0; i <= Size-1; i++ )
			for( int j = 0; j <= Size/32 - 1; j++)
				Graph[i][j] = 0;
	}
	//��ʼ��һ������Size�У�ÿ����intΪ��λ��ÿ����0/1Ϊ��λ
	
	int temp = 0;
	for( int i = 0; i <= Size-1; i++ ){//�����i������
		for( int j = 0; j <= Size-1; j++ ){//�Ե�i������������
			int Index = j / 32;
			int BitIndex = j % 32;
			scanf("%d",&temp);
			if( temp == 1 )
				Graph[i][Index] += (1 << (31-BitIndex));
		}
	}//������ݵĳ�ʼ��
	return Graph;
}

/*ȡĳ��int��ĳλ*/
int find(int &a, int index){
	if(index > 31) index %= 31;
	return ( (a>> (31-index) ) & 1 );
}

/*�Ա�ĳ��������*/
int countRelevant(int** Graph, int i, int j, int Size){
	int totalInt = (Size%32 == 0) ? Size/32 : Size/32+1;
	int Res = Size % 32;
	int count = 0;
	
	int *CmpSet1 = Graph[i], *CmpSet2 = Graph[j];
	int temp1 = CmpSet1[j/32];
	if( find(temp1, j%32) == 1 ){
		count = 0;
		return count;
	}

	for(int k = 0; k <= Size-1; k++){
		int Cmp1 = CmpSet1[k/32];
		int Cmp2 = CmpSet2[k/32];
		if( find(Cmp1, k%32)==1 && find(Cmp2, k%32)==1 )
			count++;
	}
	return count;
}

/*�����Ƽ�����*/
int **CommandMat(int** Graph, int Size){
	int **Command = new int*[Size];
	int maxInt = (Size%32==0) ? Size/32 : Size/32+1;
	for( int i = 0; i <= Size-1; i++)
		Command[i] = new int[maxInt];
	for( int i = 0; i <= Size-1; i++)
		for( int j = 0; j <= maxInt-1; j++ )
			Command[i][j] = 0;
	//��ʼ��

	for( int i = 0; i <= Size-1; i++ )
		for( int j = 0; j < i; j++ ){
			if(countRelevant(Graph,i,j,Size) >= 3){//��Ҫ����i��j��λ��1
				Command[i][j/32] += ( 1 << (31 - (j%32)) );
				Command[j][i/32] += ( 1 << (31 - (i%32)) );
			}
		}
	
	return Command;
}

/*��ӡ�Ƽ�����*/
void printBitMat(int** Max, int Size){
	int number = 0;
	for(int i = 0; i <= Size-1; i++){
		for(int j = 0; j <= Size-1; j++){
			number = (Max[i][j/32] >> (31 - j%32)) & 1 ;
			printf("%d ",number);
		}
		printf("\n");
	}
}

bool visited(vector<int> &visit, int index){
	for( int i = 0; i <= (int)visit.size()-1; i++ ){
		if( visit[i] == index ) return true;
	}
	return false;
}

/*Ѱ�ҹ���*/
void tranverse(int** Graph,
			   int thisNode,
			   int target,
			   vector<int>& visit,//�ѷ��ʵĵ�
			   stack<int>& path, //���ߵ�·��
			   int Size
			   )
{
	visit.insert(visit.end(), thisNode);
	vector<int> container;
	for(int k = 0; k <= Size-1; k++){//������k��������ҵ�
		if( ( (Graph[thisNode][k/32] >> (31-k%32)) & 1 ) == 1 ){
			if(k == target){
				
				path.push(k);
				return;
			}
			if( !visited( visit, k ) ){//����δ���ʵ�
				container.insert( container.end(), k );
			}

		}
	}
	//�����ⲽδ����
	if( container.empty() ){//���û�пɷ��ʵ�
		path.pop();//ɾ����ߵĽڵ�
		if(path.empty()) return;
		int last = path.top();
		tranverse( Graph, last, target, visit, path, Size );
	}

	else {
		int next = container[0];
		path.push(next);
		tranverse( Graph, next, target, visit, path, Size );
	}


}

void printPath(stack<int> &path){
	if( path.empty() )
		printf("-1");
	else {
		stack<int> RealPath;
		while( !path.empty() ){
			RealPath.push( path.top() );
			path.pop();
		}
		while( !RealPath.empty() ){
			printf("%d ",RealPath.top());
			RealPath.pop();
		}
	}
	printf("\n");
}



int main(){
	int Size = 0;
	scanf("%d",&Size);
	int** Graph = InitGraph(Size);
	int beginNode = 0, endNode = 0;
	scanf("%d %d",&beginNode, &endNode);
	int** BitMat = CommandMat(Graph,Size);
	stack<int> pathStack;
	vector<int> visit;
	pathStack.push(beginNode);
	tranverse( Graph, beginNode, endNode, visit, pathStack, Size );
	printBitMat(BitMat,Size);
	printPath(pathStack);
	
	getchar();
	getchar();
	delete[] Graph,BitMat;
	return 0;
}




/*test
6
1 1 0 0 1 0
1 0 1 0 1 0
0 1 0 1 0 0
0 0 1 0 1 1
1 1 0 1 0 0
0 0 0 1 0 0
5 0

11
0 0 0 0 0 0 0 0 0 0 0
0 0 1 1 1 0 0 0 0 0 0
0 1 0 0 0 1 0 0 0 0 0
0 1 0 0 0 1 0 0 0 0 0
0 1 0 0 0 1 0 0 0 0 0
0 0 1 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 1 0
0 0 0 0 0 0 1 0 0 0 1
0 0 0 0 0 0 1 0 0 0 1
0 0 0 0 0 0 1 0 0 0 1
0 0 0 0 0 0 0 1 1 1 0
0 10

4
0 1 0 0
1 0 1 0
0 1 0 1
1 0 1 0
1 2
*/