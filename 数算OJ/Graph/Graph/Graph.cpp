/*问题描述：
	推荐可能认识的用户，要求两人互不认识，且认识的相同的人大等于3
	输入一个矩阵
	输出一个矩阵（是否为可能认识）
	以及给出某两个用户可能认识的路径
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

/*思路：位运算*/
/*图的邻接矩阵初始化*/
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
	//初始化一个矩阵，Size行，每行以int为单位，每列以0/1为单位
	
	int temp = 0;
	for( int i = 0; i <= Size-1; i++ ){//输入第i行数据
		for( int j = 0; j <= Size-1; j++ ){//对第i行数据做处理
			int Index = j / 32;
			int BitIndex = j % 32;
			scanf("%d",&temp);
			if( temp == 1 )
				Graph[i][Index] += (1 << (31-BitIndex));
		}
	}//完成数据的初始化
	return Graph;
}

/*取某个int的某位*/
int find(int &a, int index){
	if(index > 31) index %= 31;
	return ( (a>> (31-index) ) & 1 );
}

/*对比某两行数据*/
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

/*生成推荐矩阵*/
int **CommandMat(int** Graph, int Size){
	int **Command = new int*[Size];
	int maxInt = (Size%32==0) ? Size/32 : Size/32+1;
	for( int i = 0; i <= Size-1; i++)
		Command[i] = new int[maxInt];
	for( int i = 0; i <= Size-1; i++)
		for( int j = 0; j <= maxInt-1; j++ )
			Command[i][j] = 0;
	//初始化

	for( int i = 0; i <= Size-1; i++ )
		for( int j = 0; j < i; j++ ){
			if(countRelevant(Graph,i,j,Size) >= 3){//需要将（i，j）位置1
				Command[i][j/32] += ( 1 << (31 - (j%32)) );
				Command[j][i/32] += ( 1 << (31 - (i%32)) );
			}
		}
	
	return Command;
}

/*打印推荐矩阵*/
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

/*寻找关联*/
void tranverse(int** Graph,
			   int thisNode,
			   int target,
			   vector<int>& visit,//已访问的点
			   stack<int>& path, //已走的路径
			   int Size
			   )
{
	visit.insert(visit.end(), thisNode);
	vector<int> container;
	for(int k = 0; k <= Size-1; k++){//若存在k，则代表找到
		if( ( (Graph[thisNode][k/32] >> (31-k%32)) & 1 ) == 1 ){
			if(k == target){
				
				path.push(k);
				return;
			}
			if( !visited( visit, k ) ){//若有未访问点
				container.insert( container.end(), k );
			}

		}
	}
	//若到这步未访问
	if( container.empty() ){//如果没有可访问点
		path.pop();//删除最高的节点
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