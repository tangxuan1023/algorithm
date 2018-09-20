#include "branch_limit.h"

BBnode::BBnode(BBnode *par, bool ch)
{
	parent = par;
	leftChild = ch;
}

BBnode::BBnode()
{
}

BBnode::~BBnode()
{
}


HeapNode::HeapNode(BBnode *node, double up, double pp, double ww, int lev)
{
	liveNode = node;
	upperProfit = up;
	profit = pp;
	weight = ww;
	level = lev;
}

HeapNode::HeapNode()
{
}

HeapNode::~HeapNode()
{
}

int HeapNode::compareTo(HeapNode o)
{
	double xup = o.upperProfit;
	if (upperProfit < xup)
		return -1;
	if (upperProfit == xup)
		return 0;
	else
		return 1;
}

Element::Element()
{
}

Element ::~Element()
{
}

Element::Element(int idd, double dd)
{
	id = idd;
	d = dd;
}

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

MaxHeap::MaxHeap(int n)
{
	maxNumber = pow((double)2, (double)n);
	nextPlace = 1;//��һ�����λ��  
	nodes = new HeapNode[maxNumber];
}

MaxHeap::MaxHeap()
{
}

MaxHeap::~MaxHeap()
{
}

void MaxHeap::put(HeapNode node)
{
	nodes[nextPlace] = node;
	nextPlace++;
	buildMaxHeap(nodes);
}

HeapNode MaxHeap::removeMax()
{
	HeapNode tempNode = nodes[1];
	nextPlace--;
	nodes[1] = nodes[nextPlace];
	buildMaxHeap(nodes);
	return tempNode;
}

void MaxHeap::heapAdjust(HeapNode *nodes, int i, int m)
{
	HeapNode tmp = nodes[i];
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

void MaxHeap::buildMaxHeap(HeapNode *nodes)  
{
	// Ϊ�������±������Ԫ�ر�Ŷ�Ӧ����0Ԫ�ز���ʹ�ã�
	// ��ˣ�nextPlace �ܱȽ��ѵ�����Ԫ�����������г��ȣ��� 1
	// �����г��� len = nextPlace - 1
	// ��һ����Ҫ����Ϊ����ѵ�Ԫ���±��Ѿ���Ӧ����� i = len / 2�����ü� 1
	/*for (int i = (nextPlace - 1) / 2; i > 0; --i) {
		heapAdjust(nodes, i, nextPlace - 1);
	}*/
	buildMaxHeapImpl(nodes, nextPlace - 1);
}
void MaxHeap::buildMaxHeapImpl(HeapNode *nodes, int len)
{
	for (int i = len / 2; i > 0; --i) {
		heapAdjust(nodes, i, len);
	}
}
