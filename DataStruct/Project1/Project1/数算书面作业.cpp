#include <iostream>
template <class ElemType> 
class CyQueue{
public:
	int front;//queue[front]是头结点，不存数据
	int rear;
	int MaxSize;
	bool flag;
	ElemType *queue;
	CyQueue(int ms){
		flag=0;front=0;rear=0;
		MaxSize=ms;
		queue=new ElemType[ms+5]; //分配一个足够大的空间
	}
	void EnQueue(CyQueue &Q, ElemType x);
	ElemType OutQueue(CyQueue& Q);
};

template <class ElemType>
void CyQueue<ElemType>::EnQueue(CyQueue &Q, ElemType x)
{
	if(flag == 1 && (rear+1)%MaxSize == front){
		cout<<"队列已满"<<endl;
		return;
	}
	else {
		rear = (rear++) % MaxSize;
		queue[rear] = x;
		if( (rear+1) % MaxSize == front ) flag = 1;
	}
}

template <class ElemType>
ElemType CyQueue<ElemType>::OutQueue(CyQueue &Q)
{
	if(flag == 0){
		cout<<"队列为空!"<<endl;
		return NULL;
	}
	else {
		int temp = front;
		front = (front+1)%MaxSize;
		if(front == rear) flag = 0;
		return queue[temp];
	}
}

void next(char* p, int n[]){
	int length = strlen(p);
	n[0] = 0;
	int index = 1, j = 0;
	while(index < length-1){
		
	}

}

