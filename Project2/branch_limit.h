#ifndef __BRANCH_LIMIT_H__
#define __BRANCH_LIMIT_H__

class PTNode {
public:
	PTNode(PTNode *par, bool ch) :parent(par), leftChild(ch) {}
	PTNode() {}
	~PTNode() {}
public:
	PTNode *parent;
	bool leftChild;   //左子节点标志  
};

template<typename T>
class HeapNode {
public:
	HeapNode(PTNode *node, T up, T pp, T ww, int lev) :
		liveNode(node), upperProfit(up),
		profit(pp), weight(ww), level(lev) {}
	HeapNode() {}
	~HeapNode() {}

	int compareTo(HeapNode node){
		T xup = node.upperProfit;
		if (upperProfit < xup) return -1;
		else if (upperProfit == xup) return 0;
		else return 1;
	}

public:
	PTNode *liveNode;
	int level;
	T upperProfit;
	T profit;
	T weight;
};

class Element
{
public:
	Element(int idd, double dd):id(idd), d(dd){}
	Element() {}
	~Element() {}
	/*int compareTo(Element x);
	bool equals(Element x);*/
	//void sort();

public:
	int id;	
	double d;
};

class MaxHeap {
public:
	MaxHeap(int n);
	MaxHeap();
	~MaxHeap();
	void put(const HeapNode<double> *node);
	void removeMax(HeapNode<double> *node);
private:
	HeapNode<double> *nodes;
	int nextPlace;
	int maxNumber;
};

typedef struct _attributes_param_s {
	double capacity;
	int table_size;
	double *weight_table;
	double *profit_table;
	double current_usage;
	double current_profit;
}attributes_param_t;

class BackPack {
public:
	BackPack();
	~BackPack();
	double bound(int i);
	void addLiveNode(double up, double pp, double ww, int lev, PTNode* par, bool ch);
	double MaxKnapsack();
	double knapsack(double *pp, double *ww, double cc, int *xx);

private:
	int     *bestX;
	MaxHeap *heap;
	attributes_param_t params;
};

int branch_limit_main();
#endif // __BRANCH_LIMIT_H__
