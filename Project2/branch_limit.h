#ifndef __BRANCH_LIMIT_H__
#define __BRANCH_LIMIT_H__

class PTNode {
public:
	PTNode(PTNode *par, bool ch) :parent(par), leftChild(ch) {}
	PTNode() {}
	~PTNode() {}
public:
	PTNode *parent;
	bool leftChild;   //the flag of left child  
};

template<typename T>
class HeapNode {
public:
	HeapNode(PTNode *node, T up, T p, T w, int lev) :
		liveNode(node), upperProfit(up),
		profit(p), weight(w), level(lev) {}
	HeapNode() {}
	~HeapNode() {}

public:
	PTNode *liveNode;
	int level;
	T upperProfit;
	T profit;
	T weight;
};

template<typename T>
class KeyValuePair
{
public:
	KeyValuePair(int k, T v):key(k), value(v){}
	KeyValuePair() {}
	~KeyValuePair() {}

public:
	int key;	  // key
	T value;  // value, template
};

class MaxHeap {
public:
	MaxHeap(int n);
	MaxHeap();
	~MaxHeap();
	void put(const HeapNode<double> *node);
	void peekMax(HeapNode<double> *node);
private:
	HeapNode<double> *nodes;
	int nextPlace;
	int maxNumber;
};

typedef struct _attributes_param_s {
	double capacity;
	int count;
	double *weight_table;
	double *profit_table;
	double curr_usage;
	double curr_profit;
}attributes_param_t;

typedef KeyValuePair<double> Element;
class BackPack {
public:
	BackPack();
	~BackPack();
	int init(double cap, int count, double *w_t, double *p_t);
	int deinit();
	double knapsack(int *bestx);

private:
	double bound(int i);
	void descendSort(Element *arr, int len);
	void addLiveNode(double up, double p, double w, int lev, PTNode *par, bool ch);
	double MaxKnapsack();

private:
	int     *mpBestX;
	double   mdBestP;
	MaxHeap *mpHeap;
	attributes_param_t mObjParams;
};

typedef int(*pfunc_compare)(const void *a, const void *b);

int branch_limit_main();
#endif // __BRANCH_LIMIT_H__
