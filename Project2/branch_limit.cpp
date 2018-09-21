#include "branch_limit.h"
#include <math.h>  
#include <stdlib.h>
#include <string.h>

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
void peekMaxImpl(HeapNode<T> *node, int *pi, HeapNode<T> *nodes)
{
	HeapNode<T> tmp_node = nodes[1];
	nodes[1] = nodes[--(*pi)];
	buildMaxHeap(nodes, *pi);
	*node = tmp_node;
}

// TODO(tangxuan): key-value swap based value
template <typename T>
static void _swap(KeyValuePair<T> &a, KeyValuePair<T> &b)
{
	T tmp_v = a.value;
	a.value = b.value;
	b.value = tmp_v;

	int tmp_k = a.key;

	a.key = b.key;
	b.key = tmp_k;
}

template <typename T>
int partition(KeyValuePair<T> *arr, int size, pfunc_compare pf_cmp)
{
	if (size < 2) return 0;
	T datum = arr[0].value; //datum
	int i = 1;
	int j = size - 1;

	for (;;) {
		//while (arr[j].d < key) j--; // descend sort
		//while (i < j && (arr[i].d > key || fabs(arr[i].d - key)< 10e-6)) i++;
		while (pf_cmp(&datum, &arr[j].value)) j--; // descend sort
		while (i < j && !pf_cmp(&datum, &arr[i].value)) i++;
		if (i >= j) break;
		_swap(arr[i], arr[j]);
	}

	_swap(arr[0], arr[j]);
	return j;
}

// TODO(tangxuan): key-value quick sort based value
template <typename T>
void quickSort(KeyValuePair<T> *arr, int size, pfunc_compare pf_cmp)
{
	if (size < 2) return;
	int pos = partition(arr, size, pf_cmp);
	quickSort(arr, pos, pf_cmp);
	quickSort(arr + pos + 1, size - pos - 1, pf_cmp);
}

// class MaxHeap
MaxHeap::MaxHeap(int n)
{
	maxNumber = (int)pow((double)2, (double)n);
	nextPlace = 1;
	nodes = new HeapNode<double>[maxNumber];
}

MaxHeap::MaxHeap()
{
}

MaxHeap::~MaxHeap()
{
	if (nodes) {
		delete[] nodes;
		nodes = NULL;
	}
}

void MaxHeap::put(const HeapNode<double> *node)
{
	putImpl(node, &nextPlace, nodes);
}

void MaxHeap::peekMax(HeapNode<double> *node)
{
	peekMaxImpl(node, &nextPlace, nodes);
}

// class BackPack 
BackPack::BackPack() :
	mpBestX(NULL), mdBestP(0.0), mpHeap(NULL)
{
	memset(&mObjParams, 0, sizeof(attributes_param_t));
}

BackPack::~BackPack()
{
	deinit();
}

double BackPack::bound(int i)
{
	int n = mObjParams.count;
	double cremain = mObjParams.capacity - mObjParams.curr_usage;
	double pro = mObjParams.curr_profit;
	while (i <= n && mObjParams.weight_table[i] <= cremain) {
		cremain -= mObjParams.weight_table[i];
		pro += mObjParams.profit_table[i];
		i++;
	}

	if (i <= n)
		pro += mObjParams.profit_table[i] / mObjParams.weight_table[i] * cremain;
	return pro;
}

static int compare(const void *a, const void *b)
{
	return (*(double*)a > *(double*)b);
}

void BackPack::descendSort(Element *arr, int len)
{
	quickSort((KeyValuePair<double>*)arr, len, &compare);
}

void BackPack::addLiveNode(double up, double p, double w, int lev, PTNode *par, bool ch)
{
	PTNode *pt_node = new PTNode(par, ch);  // TODO(tangxuan): delete this space
	HeapNode<double> *heap_node = &(HeapNode<double>(pt_node, up, p, w, lev));
	mpHeap->put(heap_node);
}

double BackPack::MaxKnapsack()
{
	int n = mObjParams.count;
	PTNode *enode = new PTNode();
	int i = 1;
	double bestp = 0;
	double up = bound(1);
	while (i != n + 1) {
		double wt = mObjParams.curr_usage + mObjParams.weight_table[i];
		if (wt <= mObjParams.capacity) {
			double tmp_bestp = mObjParams.curr_profit + mObjParams.profit_table[i];
			if (tmp_bestp > bestp) {
				bestp = tmp_bestp;
			}
			addLiveNode(up, tmp_bestp, mObjParams.curr_usage + mObjParams.weight_table[i], i + 1, enode, true);
		}

		up = bound(i + 1);
		if (up >= bestp) {
			addLiveNode(up, mObjParams.curr_profit, mObjParams.curr_usage, i + 1, enode, false);
		}

		// get the max info from the node heep
		HeapNode<double> node;
		mpHeap->peekMax(&node);
		enode = node.liveNode;
		mObjParams.curr_usage = node.weight;
		mObjParams.curr_profit = node.profit;
		up = node.upperProfit;
		i = node.level;
	} // end while loop

	for (int j = n; j > 0; j--) {
		mpBestX[j] = (enode->leftChild) ? 1 : 0;
		enode = enode->parent;
	}
	
	delete enode;
	return mObjParams.curr_profit;
}

int BackPack::init(double cap, int count, double *w_t, double *p_t)
{
	// init params
	mObjParams = { cap, count, w_t, p_t, 0.0, 0.0};
	mpBestX = new int[mObjParams.count + 1]();
	return 0;
}

int BackPack::deinit()
{
	if (mpBestX) {
		delete[] mpBestX;
		mpBestX = NULL;
	}
	if (mObjParams.profit_table) {
		delete[] mObjParams.profit_table;
		mObjParams.profit_table = NULL;
	}
	if (mObjParams.weight_table) {
		delete[] mObjParams.weight_table;
		mObjParams.weight_table = NULL;
	}
	if (mpHeap) {
		delete mpHeap;
		mpHeap = NULL;
	}

	return 0;
}

double BackPack::knapsack(int *bestx)
{
	do {
		double c = mObjParams.capacity;
		double *p = mObjParams.profit_table;
		double *w = mObjParams.weight_table;
		int n = mObjParams.count;
		Element *ratio = new Element[n]();
		// should it's compute
		bool compute_flag = true;

		double ws = 0.0;
		double ps = 0.0;
		for (int i = 0; i < n; i++) {
			ratio[i] = Element(i + 1, p[i + 1] / w[i + 1]);
			ps = ps + p[i + 1];
			ws = ws + w[i + 1];
		}

		if (ws <= c) {  // all goods can put in
			for (int j = 0; j < n; j++) {
				if (mpBestX) mpBestX[j] = 1;
			}
			mdBestP = ps;
			compute_flag = false;
		}

		if (compute_flag) {
			mObjParams.profit_table = new double[n + 1]();
			mObjParams.weight_table = new double[n + 1]();
			mpHeap = new MaxHeap(n);

			descendSort(ratio, n);
			for (int i = 0; i < n; i++) {
				mObjParams.profit_table[i + 1] = p[ratio[i].key];
				mObjParams.weight_table[i + 1] = w[ratio[i].key];
			}
			mdBestP = MaxKnapsack();

			// TODO(tangxuan): bestX
			for (int i = 0; i < n; i++) {
				bestx[ratio[i].key] = mpBestX[i + 1];
			}
		}
		delete[] ratio;
	} while (0);

	return mdBestP;
}