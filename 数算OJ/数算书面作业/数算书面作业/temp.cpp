#include <stdio.h>
/*HA��HBΪ�ǵݼ��������������ϲ�Ϊ�ǵݼ�������������HC
HA.head�ǵ�һ�����
�����������Ϊ
	
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