#include <iostream>
#include <stack>
#include <queue>
#include <stdio.h>
using namespace std;
#define hasLeftChild(x) (x->leftChild != NULL)
#define hasRightChild(x) (x->rightChild != NULL)
#define hasYtree(x) (x->yTree != NULL)
#define isLeftChild(x) (x == x->parent->leftChild)
#define isRightChild(x) (x == x->parent->rightChild)

/*����Ϊ�ṹ��*/
struct treeNode {
	int x;
	int y;
	treeNode* leftChild;
	treeNode* rightChild;
	treeNode* parent;
	int* yTree;
	int yTreeNum;
	treeNode(int _x, int _y){
		x = _x; y = _y;
		leftChild = NULL;
		rightChild = NULL;
		parent = NULL;
		yTree= NULL;
	}//yTreeֱ����y��int����
	treeNode(){x = 0; y = 0; leftChild = rightChild = parent = NULL; yTree = NULL; yTreeNum = 0;} 
};

struct searchPoint {
	int x;
	int y;
	int dis;
	searchPoint(int _x, int _y, int _d){
		x = _x; y = _y; dis = _d;
	}
	searchPoint(){};
};

class RangeTree {
public:
	treeNode* _root;
	treeNode* elem;
	int elemNum;
public:
	void mergeSort(int lo, int hi);
	void merge(int lo, int mi, int hi);
	//����x������
	int* mergeYtree(treeNode* left, treeNode* right);
	void insertSelfY(treeNode*);
	void buildYtree(treeNode*);
	//����Ytree�Ľ���
	int BioSearch(searchPoint range);//���ز�ѯ���ĵ���
	int find(int);
	int find(treeNode *,int);//��ĳ�ڵ����yTree
	int find(int*, int lo, int hi, int value);//��yTree�в���
	treeNode* findMaxCommonAnc(searchPoint range);//���ҹ�������
	//���Һ���
	void buildTree();
	treeNode* buildBST( treeNode* , int lo, int hi );
	//������
	RangeTree(treeNode* _elem, int sum){
		elem = _elem;
		_root = NULL;
		elemNum = sum;
	}
	~RangeTree(){
		for(int i = 0; i <= elemNum-1; i++){
			delete[] elem[i].yTree;
		}
		delete[] elem;
	}
	/*void printTree(){printTree(_root);}//for(int i = 0; i <= elemNum-1; i++) printf("%d %d %d\n", i, elem[i].x, elem[i].y );}
	void printTree(treeNode* root){
		//printf("%d\n",root->x);
		queue<treeNode*> QU;
		QU.push(root);
		//if(hasLeftChild(root))QU.push(root->leftChild);
		//if(hasRightChild(root))QU.push(root->rightChild);
		while(!QU.empty()){
			treeNode* temp = QU.front();
			QU.pop();
			printf("%d, Ytree is ",temp->x);
			for(int i = 0; i <= temp->yTreeNum-1; i++)printf("%d ",temp->yTree[i]);
			printf("\n");
			if(hasLeftChild(temp))QU.push(temp->leftChild);
			if(hasRightChild(temp))QU.push(temp->rightChild);
		}

		//if(hasLeftChild(root))
		//	printTree(root->leftChild);
		//if(hasRightChild(root))
	//		printTree(root->rightChild);
		//if(!hasLeftChild(root) && !hasRightChild(root)) printf("%d it's a leaf\n",root->x);
	}*/
};

/*����������������*/
void RangeTree::mergeSort(int lo,  int hi){
	if(hi - lo < 2) return;
	int mi = (hi + lo)/2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

void RangeTree::merge(int lo, int mi, int hi){
	//�����Ѿ�����
	treeNode* temp = new treeNode[hi-lo];
	int index1 = lo, index2 = mi, index = 0;
	while( index1 < mi && index2 < hi)
		temp[index++] = (elem[index1].x <= elem[index2].x) ? elem[index1++] : elem[index2++];
	for(;index1 < mi; temp[index++] = elem[index1++]);
	for(;index2 < hi; temp[index++] = elem[index2++]);
	for(int i = lo; i < hi; i++)elem[i] = temp[i-lo];
	delete[] temp;
}//��x����

treeNode* RangeTree::buildBST(treeNode* _elem, int lo, int hi){
	if( hi - lo == 1) return _elem+lo;
	else if( hi - lo == 0 ) return NULL;
	else {
		int mi = (lo+hi)>>1;
		_elem[mi].leftChild = buildBST(_elem, lo, mi);
		_elem[mi].rightChild = buildBST(_elem, mi+1, hi);
		if( _elem[mi].leftChild != NULL ) _elem[mi].leftChild->parent = _elem+mi;
		if( _elem[mi].rightChild != NULL ) _elem[mi].rightChild->parent = _elem+mi;
		return _elem+mi;
	}
}//�ݹ齨�������������

void RangeTree::buildYtree(treeNode* root){
	if(hasLeftChild(root) && hasRightChild(root)){
		if(!hasYtree(root->leftChild)) buildYtree(root->leftChild);
		if(!hasYtree(root->rightChild)) buildYtree(root->rightChild);//���ޣ��Ƚ���
		root->yTree = mergeYtree(root->leftChild, root->rightChild);//��merge
		root->yTreeNum = root->leftChild->yTreeNum + root->rightChild->yTreeNum + 1;
		insertSelfY(root);
	}
	else if(!hasLeftChild(root) && !hasRightChild(root)){//�����ӽڵ�
		root->yTree = new int;
		root->yTree[0] = root->y;
		root->yTreeNum = 1;
	}
	else {//����һ���ӽڵ�
		treeNode* singleChild = hasLeftChild(root) ? root->leftChild : root->rightChild;
		if(!hasYtree(singleChild)) buildYtree(singleChild);
		root->yTree = new int[root->yTreeNum = singleChild->yTreeNum + 1];
		for(int i = 0; i <= root->yTreeNum - 2; i++)
			root->yTree[i] = singleChild->yTree[i];
		insertSelfY(root);
	}

}

int* RangeTree::mergeYtree(treeNode* left, treeNode* right){//��Ȼ�Ѵ���
	int *temp = new int[left->yTreeNum + right->yTreeNum + 1];
	int i = 0, j = 0, count = 0;
	while(i < left->yTreeNum && j < right->yTreeNum ){
		temp[count++] = (left->yTree[i] <= right->yTree[j]) ? left->yTree[i++] : right->yTree[j++];
	}
	for(;i < left->yTreeNum; temp[count++] = left->yTree[i++]);
	for(;j < right->yTreeNum; temp[count++] = right->yTree[j++]);
	//mergesort in ytree
	return temp;
}

void RangeTree::insertSelfY(treeNode* root){
	if(root->yTree == NULL) return;
	int i = 0;
	while( i < root->yTreeNum-1 && root->y > root->yTree[i] )i++;//ͣ��С�ڵ�λ��
	for( int j = root->yTreeNum-1; j > i; j-- )root->yTree[j] = root->yTree[j-1];
	root->yTree[i] = root->y;
}//��ɲ���

void RangeTree::buildTree(){
	mergeSort(0,elemNum);//����
	_root = buildBST(elem, 0, elemNum);//����BST;
	buildYtree(_root);//������yTree
}

/*���Ҳ���*/
//yTree����
int RangeTree::find(int* set, int lo, int hi, int value){
	if(hi -lo == 1){
		if( set[lo] < value ) return hi;
		else if( set[lo] >= value ) return lo;//���ش���ڵ���С����
	}
	else if(hi == lo) return lo;
	else {
		int mi = (lo+hi)>>1;
		if( set[mi] == value )return mi;
		else if( set[mi] > value ) return find(set, lo, mi, value);
		else if( set[mi] < value ) return find(set, mi+1, hi, value); 
	}
}

//ĳ�ڵ����yTree
int RangeTree::find(treeNode* root, int value){
	return find(root->yTree,0,root->yTreeNum,value);
}

//�������
int RangeTree::find(int value){
	treeNode* node = _root;
	while( node != NULL){
		if( node->x == value )return node-elem;//������������ֵ
		else if( node->x > value ) {
			if( hasLeftChild(node) )
				node = node->leftChild;
			else return node-elem;
		}
		else {
			if( hasRightChild(node) )
				node = node->rightChild;
			else
				return node-elem+1;
			}
		}
}
//��������ѹ�������
treeNode* RangeTree::findMaxCommonAnc(searchPoint range){
	int lo_x = range.x - range.dis;
	int hi_x = range.x + range.dis;
	treeNode* ancestor = _root;
	while(ancestor != NULL){
		if( lo_x < ancestor->x && hi_x < ancestor->x ){
			if( hasLeftChild(ancestor) ) 
				ancestor = ancestor->leftChild;
			else 
				return ancestor;
		}
		else if( lo_x > ancestor->x && hi_x > ancestor->x ){
			if( hasRightChild(ancestor) )
				ancestor = ancestor->rightChild;
			else 
				return ancestor;
		}
		else //���ַ���
			return ancestor;
	}
}

int RangeTree::BioSearch(searchPoint range){
	int lo_x = range.x - range.dis;
	int hi_x = range.x + range.dis;
	int lo_y = range.y - range.dis;
	int hi_y = range.y + range.dis;
	int count = 0;
	//��Χ
	int loIndex = find(lo_x);
	int hiIndex = (find(hi_x) < elemNum && elem[find(hi_x)].x == hi_x) ? find(hi_x) : find(hi_x)-1;
	//�ҵ�����������߽�
	treeNode* ancestor = findMaxCommonAnc(range);
	treeNode* leftSide = ancestor;
	treeNode* rightSide = ancestor;
	if( ancestor->y <= hi_y && ancestor->y >= lo_y ) count+=1;
	stack<treeNode*> nodes;

	int loValue = elem[loIndex].x;
	int hiValue = elem[hiIndex].x;
	if( elem[loIndex].y <= hi_y && elem[loIndex].y >= lo_y && elem+loIndex != ancestor)count++;
	if( elem[hiIndex].y <= hi_y && elem[hiIndex].y >= lo_y && elem+hiIndex != ancestor)count++;
	treeNode* left = (ancestor->x == loValue) ? ancestor : ancestor->leftChild;
	treeNode* right = (ancestor->x == hiValue) ? ancestor : ancestor->rightChild;

	while( left!= NULL && left->x != loValue ){
		if( left->x > loValue ){
			if( hasRightChild(left) )
				nodes.push(left->rightChild);
			if( left->y <= hi_y && left->y >= lo_y )
				count++;
			left = left->leftChild;
		}
		else if( left->x < loValue ){
			left = left->rightChild;
		}
	}
	if(hasRightChild(left) && left != ancestor)nodes.push(left->rightChild);
	/*if( left->x == loValue ){
		printf("��ѭ�����\n");
	}
	*/
	while( right!= NULL && right->x != hiValue ){
		if( right->x < hiValue ){
			if( hasLeftChild(right) )
				nodes.push(right->leftChild);
			if(right->y <= hi_y && right->y >= lo_y )
				count++;
			right = right->rightChild;
		}
		else if( right->x > hiValue ){
			right = right->leftChild;
		}
	}
	if(hasLeftChild(right) && right != ancestor)nodes.push(right->leftChild);
	/*if( right->x == hiValue ){
		printf("��ѭ�����\n");
		
	}
	*/
	//���˽����е��ҵ�
	//���±���yTree
	while( !nodes.empty() ){
		treeNode* temp = nodes.top();
		nodes.pop();
		int hi = find(temp->yTree, 0, temp->yTreeNum, hi_y);
		if( hi >= temp->yTreeNum || temp->yTree[hi] != hi_y ) hi--;
		int lo = find(temp->yTree, 0 ,temp->yTreeNum, lo_y);
		count += hi-lo+1;
	}
	return count;
}
