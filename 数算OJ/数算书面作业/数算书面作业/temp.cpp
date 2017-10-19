#include <stdio.h>
/*HA和HB为非递减有序线性链表，合并为非递减有序线性链表HC
HA.head是第一个结点
结点数据类型为
	
*/
struct SNode{
		int data;
		SNode *next;
		SNode():data(0),next(NULL){}
	};
typedef SNode LinkList;
void insert(LinkList&, int );
void mergeList(LinkList &HA,LinkList &HB,LinkList &HC){
	SNode *A = &HA, *B = & HB;
	while( A != NULL && B != NULL ){
		if( A->data < B->data ){
			insert( HC, A->data );
			
}