#include <iostream>
template <class ElemType> 
class CyQueue{
public:
	int front;//queue[front]��ͷ��㣬��������
	int rear;
	int MaxSize;
	bool flag;
	ElemType *queue;
	CyQueue(int ms){
		flag=0;front=0;rear=0;
		MaxSize=ms;
		queue=new ElemType[ms+5]; //����һ���㹻��Ŀռ�
	}
	void EnQueue(CyQueue &Q, ElemType x);
	ElemType OutQueue(CyQueue& Q);
};

template <class ElemType>
void CyQueue<ElemType>::EnQueue(CyQueue &Q, ElemType x)
{
	if(flag == 1 && (rear+1)%MaxSize == front){
		cout<<"��������"<<endl;
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
		cout<<"����Ϊ��!"<<endl;
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

