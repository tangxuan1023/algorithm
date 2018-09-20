#include "branch_limit.h"
#include <math.h>  

int Element::compareTo(Element x)
{
	double xd = x.d;
	if (d < xd)return -1;
	if (d == xd)return 0;
	return 1;
}

bool Element::equals(Element x)
{
	return d == x.d;
}

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

MaxHeap::MaxHeap(int n)
{
	maxNumber = pow((double)2, (double)n);
	nextPlace = 1;//下一个存放位置  
	nodes = new HeapNode<double>[maxNumber];
}

MaxHeap::MaxHeap()
{
}

MaxHeap::~MaxHeap()
{
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

void MaxHeap::put(const HeapNode<double> *node)
{
	putImpl(node, &nextPlace, nodes);
}

void MaxHeap::removeMax(HeapNode<double> *node)
{
	removeMaxImpl(node, &nextPlace, nodes);
}
