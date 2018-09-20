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
	nextPlace = 1;//��һ�����λ��  
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
	// TODO(tangxuan): �޸���ƣ����� 0 Ԫ��Ҳ��Ϊ��Чʹ�ÿռ�
	// Ϊ�������±������Ԫ�ر�Ŷ�Ӧ���� 0 Ԫ�ز���ʹ�ã�
	// ��ˣ�nextPlace �ܱȽ��ѵ�����Ԫ�����������г��ȣ��� 1
	// �����г��� len = nextPlace - 1
	// ��һ����Ҫ����Ϊ����ѵ�Ԫ���±��Ѿ���Ӧ����� i = len / 2�����ü� 1
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
