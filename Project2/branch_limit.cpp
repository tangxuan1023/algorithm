#include "branch_limit.h"
#include <math.h>  
#include <stdlib.h>

// template
template<typename T>
void heapAdjust(HeapNode<T> *nodes, int i, int m)
{
	HeapNode<T> tmp = nodes[i];
	for (int k = 2 * i; k <= m; k *= 2) {
		if (k < m && nodes[k + 1].upperProfit > nodes[k].upperProfit)
			++k;
		if (!(tmp.upperProfit < nodes[k].upperProfit))
			break;
		nodes[i] = nodes[k];
		i = k;
	}
	nodes[i] = tmp;
}

template<typename T>
void buildMaxHeapImpl(HeapNode<T> *nodes, int len)
{
	for (int i = len / 2; i > 0; --i) {
		heapAdjust(nodes, i, len);
	}
}

template<typename T>
void buildMaxHeap(HeapNode<T> *nodes, int nextPlace)
{
	// TODO(tangxuan): 修改设计，将第 0 元素也作为有效使用空间
	// 为了数组下标和序列元素编号对应，第 0 元素不作使用，
	// 因此，nextPlace 总比建堆的序列元素总量（序列长度）多 1
	// 即序列长度 len = nextPlace - 1
	// 第一个需要调整为大根堆的元素下标已经对应，因此 i = len / 2，不用减 1
	/*for (int i = (nextPlace - 1) / 2; i > 0; --i) {
	heapAdjust(nodes, i, nextPlace - 1);
	}*/
	buildMaxHeapImpl(nodes, nextPlace - 1);
}

template<typename T>
void putImpl(const HeapNode<T> *node, int *pi, HeapNode<T> *nodes)
{
	nodes[(*pi)++] = *node;
	buildMaxHeap(nodes, *pi);
}

template<typename T>
void removeMaxImpl(HeapNode<T> *node, int *pi, HeapNode<T> *nodes)
{
	HeapNode<T> tmpNode = nodes[1];
	nodes[1] = nodes[--(*pi)];
	buildMaxHeap(nodes, *pi);
	*node = tmpNode;
}


// TODO(tangxuan): key-value swap based value
void _swap(Element &a, Element &b)
{
	double tmp = a.d;
	a.d = b.d;
	b.d = tmp;

	int tmp1 = a.id;

	a.id = b.id;
	b.id = tmp1;
}


// class interface
//int Element::compareTo(Element x)
//{
//	double xd = x.d;
//	if (d < xd)return -1;
//	if (d == xd)return 0;
//	return 1;
//}
//
//bool Element::equals(Element x)
//{
//	return d == x.d;
//}

//typedef int (*pf_compare)(const void *a, const void *b);
//
//int compare(const void *a, const void *b)
//{
//	return (*(double*)b > *(double*)a);
//}

int partition(Element *arr, int size/*, pf_compare cmp*/)
{
	if (size < 2) return 0;
	double key = arr[0].d;
	int i = 1;
	int j = size - 1;

	for (;;) {
		while (arr[j].d < key) j--; // descend sort
		while (i < j && arr[i].d > key) i++;
		if (i >= j) break;
		_swap(arr[i], arr[j]);
	}

	_swap(arr[0], arr[j]);
	return j;
}

// TODO(tangxuan): key-value quick sort based value
void quickSort(Element *arr, int size)
{
	if (size < 2) return;
	int pos = partition(arr, size/*, &compare*/);
	quickSort(arr, pos);
	quickSort(arr + pos + 1, size - pos - 1);
}

void descend_sort(Element *arr, int size)
{
	quickSort(arr, size);
}

MaxHeap::MaxHeap(int n)
{
	maxNumber = pow((double)2, (double)n);
	nextPlace = 1;
	nodes = new HeapNode<double>[maxNumber];
}

MaxHeap::MaxHeap()
{
}

MaxHeap::~MaxHeap()
{
	if (nodes) {
		delete nodes;
		nodes = NULL;
	}
}

void MaxHeap::put(const HeapNode<double> *node)
{
	putImpl(node, &nextPlace, nodes);
}

void MaxHeap::removeMax(HeapNode<double> *node)
{
	removeMaxImpl(node, &nextPlace, nodes);
}


// class BackPack function
BackPack::BackPack() 
{ 
	/*double w_t[] = { 0, 16, 15, 15, 15 };
	double p_t[] = { 0, 45, 25, 25, 30 };

	params = { 30, 4, w_t, p_t, 0, 0 };
	bestX = new int[params.table_size];
	heap = new MaxHeap(params.table_size); */
}

BackPack::~BackPack() 
{
	/*if (bestX) {
		delete bestX;
		bestX = NULL;
	}
	if (heap) {
		delete heap;
		heap = NULL;
	}*/
}
 
double BackPack::bound(int i)
{
	int n = params.table_size;
	double cleft = params.capacity - params.current_usage;
	double b = params.current_profit;
	while (i <= n && params.weight_table[i] <= cleft) {
		cleft = cleft - params.weight_table[i];
		b = b + params.profit_table[i];
		i++;
	}

	if (i <= n)
		b = b + params.profit_table[i] / params.weight_table[i] * cleft;
	return b;
}
  
void BackPack::addLiveNode(double up, double pp, double ww, int lev, PTNode* par, bool ch)
{
	PTNode *b = new PTNode(par, ch);
	HeapNode<double> *node = &(HeapNode<double>(b, up, pp, ww, lev));
	heap->put(node);
}

double BackPack::MaxKnapsack()
{
	int n = params.table_size;
	PTNode * enode = new PTNode();
	int i = 1;
	double bestp = 0;  
	double up = bound(1); 
	while (i != n + 1) { 
		double wt = params.current_usage + params.weight_table[i];
		if (wt <= params.capacity) {
			if (params.current_profit + params.profit_table[i] > bestp)
				bestp = params.current_profit + params.profit_table[i];
			addLiveNode(up, params.current_profit + params.profit_table[i],
				params.current_usage + params.weight_table[i], i + 1, enode, true);
		}
		up = bound(i + 1);
		if (up >= bestp)
			addLiveNode(up, params.current_profit, params.current_usage, i + 1, enode, false);
		HeapNode<double> node;
		heap->removeMax(&node);
		enode = node.liveNode;
		params.current_usage = node.weight;
		params.current_profit = node.profit;
		up = node.upperProfit;
		i = node.level;
	}
	for (int j = n; j > 0; j--) {

		bestX[j] = (enode->leftChild) ? 1 : 0;
		enode = enode->parent;
	}
	return params.current_profit;
}

double BackPack::knapsack(double *pp, double *ww, double cc, int *xx)
{ 
	int c = params.capacity = cc; 
	int n = params.table_size = 4;
	Element *q = new Element[n];
	double ws = 0.0;
	double ps = 0.0;
	q[0] = { 0,0 };
	for (int i = 0; i < n; i++) {
		q[i] = Element(i + 1, pp[i + 1] / ww[i + 1]);
		ps = ps + pp[i + 1];
		ws = ws + ww[i + 1];
	}
	if (ws <= c) {
		return  ps;
	}
	// sort the array q, based q[i].d 
	descend_sort(q, 4);

	params.profit_table = new double[n + 1];
	params.weight_table = new double[n + 1];
	for (int i = 0; i < n; i++) {
		params.profit_table[i + 1] = pp[q[i].id];
		params.weight_table[i + 1] = ww[q[i].id];
	}
	params.current_usage = 0.0;
	params.current_profit = 0.0;
	bestX = new int[n + 1];
	heap = new MaxHeap(n);
	double bestp = MaxKnapsack();
	for (int j = 0; j < n; j++)
		xx[q[j].id] = bestX[j + 1];

	return  bestp;
}