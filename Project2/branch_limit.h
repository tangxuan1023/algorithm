#ifndef __BRANCH_LIMIT_H__
#define __BRANCH_LIMIT_H__

#include <math.h>  

class BBnode {
public:
	BBnode *parent;
	bool leftChild;   //左子节点标志  
	BBnode(BBnode *par, bool ch);
	BBnode();
	~BBnode();
};

class HeapNode {
public:
	BBnode* liveNode; // 活结点  
	double  upperProfit; //价值上界  
	double  profit; //价值  
	double  weight; //重量  
	int     level; // 活结点在子集树中所处的层次  
	HeapNode(BBnode *node, double up, double pp, double ww, int lev);
	HeapNode();
	~HeapNode();
	int compareTo(HeapNode o);
};

class Element
{
private:
	double d;
public:
	int id;
	Element();
	Element(int idd, double dd);
	~Element();
	int compareTo(Element x);
	bool equals(Element x);
};

class MaxHeap {
private:
	HeapNode *nodes;
	int nextPlace;
	int maxNumber;
	void buildMaxHeapImpl(HeapNode *nodes, int len);
public:
	MaxHeap(int n);
	MaxHeap();
	~MaxHeap();
	void put(HeapNode node);
	HeapNode removeMax();
	void heapAdjust(HeapNode *nodes, int s, int m);
	void buildMaxHeap(HeapNode *nodes);	
};

int branch_limit_main();
#endif // __BRANCH_LIMIT_H__
