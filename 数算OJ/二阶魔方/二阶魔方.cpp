#define _CRT_SECURE_NO_WARNINGS
#include <unordered_map>
#include <stdio.h>
#include <queue>
#include <stack>
//9种操作
const short F1 = 1;
const short F2 = 2;
const short F3 = 3;
const short R1 = 4;
const short R2 = 5;
const short R3 = 6;
const short U1 = 7;
const short U2 = 8;
const short U3 = 9;

//6种颜色
const int yellow = 0;
const int green  = 1;
const int orange = 2;
const int blue   = 3;
const int red    = 4;
const int white  = 5;

const int index[9][24] = {//旋转后的对照表
	{0,1,13,5,4,20,14,6,2,9,10,11,12,21,15,7,3,17,18,19,16,8,22,23},
	{0,1,21,20,4,16,15,14,13,9,10,11,12,8,7,6,5,17,18,19,3,2,22,23},
	{0,1,8,16,4,3,7,15,21,9,10,11,12,2,6,14,20,17,18,19,5,13,22,23},
	{0,7,2,15,4,5,6,21,16,8,3,11,12,13,14,23,17,9,1,19,20,18,22,10},
	{0,21,2,23,4,5,6,18,17,16,15,11,12,13,14,10,9,8,7,19,20,1,22,3},
	{0,18,2,10,4,5,6,1,9,17,23,11,12,13,14,3,8,16,21,19,20,7,22,15},
	{2,0,3,1,6,7,8,9,10,11,4,5,12,13,14,15,16,17,18,19,20,21,22,23},
	{3,2,1,0,8,9,10,11,4,5,6,7,12,13,14,15,16,17,18,19,20,21,22,23},
	{1,3,0,2,10,11,4,5,6,7,8,9,12,13,14,15,16,17,18,19,20,21,22,23}
};
//该魔方组成:yellow 0 To white 5, green 1  To blue 3, orange 2 To red 4
using namespace std;
struct Node	{
	long long status;		//表示状态
	//Node* parent;			//上一个节点指针
	short lastOperation;	//上一次操作,即可还原
	short layer;			//层数
	short visitedState;		//已访问过的点
	Node(){}
	Node(long long s,short last,short l){
		layer = l;
		lastOperation = last;
		status = s;
		visitedState = 0;
	}

};

short getOpposedOp(short operation){
	switch(operation){
	case F1:return F3;
	case F2:return F2;
	case F3:return F1;
	case R1:return R3;
	case R2:return R2;
	case R3:return R1;
	case U1:return U3;
	case U2:return U2;
	case U3:return U1;
	}

}

void printOperation(short op){
	switch (op)
	{
	case F1:printf("F+\n");break;
	case F2:printf("F2\n");break;
	case F3:printf("F-\n");break;
	case R1:printf("R+\n");break;
	case R2:printf("R2\n");break;
	case R3:printf("R-\n");break;
	case U1:printf("U+\n");break;
	case U2:printf("U2\n");break;
	case U3:printf("U-\n");break;
	default:
		break;
	}
}

long long createStatus(int* m){//将数组还原为一个longlong
	long long status = 0;
	for(int i = 0; i <= 23; i++){
		status *= 6;
		status += m[i];
	}
	return status;
}

long long operation(short method, long long origin){//将魔方操作对应
	long long finalStatus = 0;
	int *tempArray = new int[24](),*finalArray = new int[24]();
	for(int i = 0; i <= 23; i++){
		tempArray[23-i] = origin%6;
		origin /= 6;
	}
	for(int i = 0; i <= 23; i++)
		finalArray[i] = tempArray[index[method-1][i]];

	for(int i = 0; i <= 23; i++){
		finalStatus *= 6;
		finalStatus += finalArray[i];
	}
	delete[] finalArray,tempArray;
	return finalStatus;
}

int getOpposedColor(int color){
	switch (color)
	{
	case green:		return blue;
	case blue:		return green;
	case orange:	return red;
	case red:		return orange;
	case white:		return yellow;
	case yellow:	return white;
	default:
		break;
	}
}

long long findFinalStatus(int* origin){//找到最终的状态
	long long finalState = 0;
	int left = origin[12];
	int down = origin[22];
	int back = origin[19];
	int front = getOpposedColor(back);
	int up = getOpposedColor(down);
	int right = getOpposedColor(left);
	int *m = new int[24];
	m[0] = m[1] = m[2] = m[3] = up;
	m[4] = m[5] = m[12] = m[13] = left;
	m[6] = m[7] = m[14] = m[15] = front;
	m[8] = m[9] = m[16] = m[17] = right;
	m[10] = m[11] = m[18] = m[19] = back;
	m[20] = m[21] = m[22] = m[23] = down;
	for(int i = 0; i <= 23; i++){
		finalState *= 6;
		finalState += m[i];
	}
	delete []m;
	return finalState;
}

long long powInt(long long  x, int i){
	if( i == 0 )return 1;
	long long origin = x;
	for(int j = 0; j <= i-1; j++)
		x *= origin;
	return x;
}

int getCertainNumber(long long status, int i){//找到某个面的数
	long long mo = powInt(6,23-i+1);
	return (int)((status % mo)/powInt(6,23-i));
}

void printMofang(long long x){
	int* m = new int[24]();
	for(int i = 0; i <= 23; i++){
		m[23-i] = x%6;
		x /= 6;
	}
	
	printf("    %d %d \n",m[0],m[1]);
	printf("    %d %d \n",m[2],m[3]);
	printf("%d %d %d %d %d %d %d %d\n",m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11]);
	printf("%d %d %d %d %d %d %d %d\n",m[12],m[13],m[14],m[15],m[16],m[17],m[18],m[19]);
	printf("    %d %d \n",m[20],m[21]);
	printf("    %d %d \n",m[22],m[23]);
	delete[] m;

}


long long getInsertState(queue<Node>& queue1, queue<Node>& queue2,
				   unordered_map<long long,Node>& hash1,
				   unordered_map<long long,Node>& hash2){
					   //找到相交的点
	int thisLayer = 0;
	bool find = false;
	while(!find){
		//printf("thisLayer:%d\n",thisLayer);
		while(queue1.front().layer == thisLayer){//队列1的循环
			Node temp = queue1.front();
			while(temp.visitedState < 9){//若该节点的子节点还没访问完
				long long newState = operation(temp.visitedState+1,temp.status);
				if(hash2.count(newState) > 0){//代表已找到
					if(hash1.count(newState) == 0)
						hash1.insert(std::make_pair(newState,Node(newState,temp.visitedState+1,thisLayer+1)));
					return newState;
				}
				else if(hash1.count(newState) > 0){//代表之前已经访问过
					temp.visitedState++;
					continue;
				}
				else {//未出现过的节点
					//printf("add new Node: %d",newState);
					//printMofang(newState);
					Node thisNode(newState,temp.visitedState+1,thisLayer+1);
					queue1.push(thisNode);
					hash1.insert(std::make_pair(newState,thisNode));
					temp.visitedState++;
				}
			}
			//printf("delete1\n");
			queue1.pop();
		}//将队列1中该层的点全部访问完

		while(queue2.front().layer == thisLayer){//队列2循环
			Node temp = queue2.front();
			while(temp.visitedState < 9){
				long long newState = operation(temp.visitedState+1,temp.status);
				if(hash1.count(newState) > 0){
					if(hash2.count(newState) == 0)
						hash2.insert(std::make_pair(newState,Node(newState,temp.visitedState+1,thisLayer+1)));
					return newState;
				}
				else if(hash2.count(newState) > 0){
					temp.visitedState++;
					continue;
				}
				else {
					//printf("add new Node: %d",newState);
					//printMofang(newState);
					Node thisNode(newState,temp.visitedState+1,thisLayer+1);
					queue2.push(thisNode);
					hash2.insert(std::make_pair(newState,thisNode));
					temp.visitedState++;
				}
				
			}
			//printf("delete2\n");
			queue2.pop();
		}
		thisLayer++;
	}
	return 0;
}
void printMofangTrace(long long insertState,
					  unordered_map<long long,Node>& hash1,
					  unordered_map<long long,Node>& hash2,
					  long long originState,
					  long long finalState){//倒推
	Node first = hash1.find(insertState)->second;
	Node second = hash2.find(insertState)->second;
	stack<short> help;
	
	while(first.status != originState){
		help.push(first.lastOperation);
		long long last = operation(getOpposedOp(first.lastOperation),first.status);
		if(!(hash1.find(last) == hash1.end()))
			first = hash1.find(last)->second;
		else {
			printf("first:\n");
			printMofang(first.status);
			printOperation(getOpposedOp(first.lastOperation));
			printMofang(last);
			break;
		}
	}
	while(!help.empty()){
		printOperation(help.top());
		help.pop();
	}
	while(second.status != finalState){
		printOperation(getOpposedOp(second.lastOperation));
		second = hash2.find(operation(getOpposedOp(second.lastOperation),second.status))->second;
	}


}
void test(unordered_map<long long,Node>& hash1){
	hash1.insert(std::make_pair(10,Node(10,0,0)));
}

int main(){
	int *originArray = new int[24]();
	for(int i = 0; i <= 23; i++)
		scanf("%d",originArray+i);

	long long originState = createStatus(originArray);
	long long finalState  = findFinalStatus(originArray);
	if(originState == finalState){
		printf("0\n");
		return 0;
	}
	
	Node originNode(originState,0,0);
	Node finalNode(finalState,0,0);
	//0代表未操作
	
	queue<Node> first,second;
	first.push(originNode);
	second.push(finalNode);
	unordered_map<long long,Node> hash1;
	unordered_map<long long,Node> hash2;
	
	hash1.insert(std::make_pair(originState,originNode));
	hash2.insert(std::make_pair(finalState,finalNode));
	//printf("执行到此\n");
	long long insertState = getInsertState(first,second,hash1,hash2);
	printf("%d\n",hash1.find(insertState)->second.layer+hash2.find(insertState)->second.layer);//打印次数
	printMofangTrace(insertState,hash1,hash2,originState,finalState);

	/*printf("original:\n");
	printMofang(originState);
	
	//printMofang(finalState);
	long long temp = 0;
	temp = operation(U3,originState);
	printf("\n:\n");
	printMofang(temp);*/

	getchar();
	//delete[] originArray;
	return 0;
}
/*
    0 4
    2 2
4 3 0 0 1 3 5 3
1 0 1 2 5 3 5 4
    4 1
    5 2
	*/