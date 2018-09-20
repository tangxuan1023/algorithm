#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//sort algorithm

void selectSort(int *arr, int size)
{
	int i, j, min;  // min 为当前最小数的下标
	for (i = 0; i < size; i++) { // 选择放在第 i 个位置的数
		min = i;  // 假设当前位置的数最小
		for (j = i + 1; j < size; j++) { // 遍历后面的数，看是否有更小的
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap<int>(arr[i], arr[min]); // 将目前最小的数交换到当前位置，当前位置以前的数皆有序
	}
}


static int *divide(int *arr, int start, int size)
{
	int *array = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		array[i] = arr[start + i];
	}
	return array;
}

static void merge(int *arr, int *partArr1, int size1, int *partArr2, int size2)
{
	int i, j, k;
	i = j = k = 0;
	while (i < size1 && j < size2) {
		if (partArr1[i] < partArr2[j]) {
			arr[k++] = partArr1[i++];
		}
		else {
			arr[k++] = partArr2[j++];
		}
	}

	while (i < size1) arr[k++] = partArr1[i++];
	while (j < size2) arr[k++] = partArr2[j++];
}


void mergeSort(int *arr, int size)
{
	if (size <= 1) return;
	int size1 = size >> 1;
	int size2 = size - size1;
	int *arr1 = divide(arr, 0, size1);
	int *arr2 = divide(arr, size1, size2);
	mergeSort(arr1, size1);
	mergeSort(arr2, size2);  // 递归使用不当可能会造成栈溢出的问题
	merge(arr, arr1, size1, arr2, size2);

	free(arr1); arr1 = NULL;
	free(arr2); arr2 = NULL;
}

int partition(int *arr, int size)
{
	if (size < 2) return 0;
	int key = arr[0];
	int i = 1;//low;
	int j = size - 1;//high + 1;

	for (;;) {
		//do j--; while (arr[j] > key);
		while (arr[j] < key) j--; // 升降序控制
		//do i++; while (i <= high && arr[i] < key);
		while (i < size && arr[i] > key) i++; // 升降序控制
		if (i >= j) break;
		swap<int>(arr[i], arr[j]);
	}

	swap<int>(arr[0], arr[j]);
	return j;
}

void quickSort(int *arr, int size)
{
	if (size < 2) return;
	int pos = partition(arr, size);
	quickSort(arr, pos);
	quickSort(arr + pos + 1, size - pos - 1);
}

void quick_sort(int *arr, int size)
{
	if (size < 2) return;
	int *stk = (int*)malloc((size) * sizeof(int));
	int p = 0;
	int l, r, m;
	// 通过记录子数组左右边界来实现递归分解
	stk[p++] = 0;
	stk[p++] = size - 1;
	m = 0;
	while (p != 0) {
		r = stk[--p];
		l = stk[--p];
		if (l < r) {
			// 注意，对子数组的划分得到的 基准位置 m 的值是相对于子数组偏移的，
			// 故相对于原始数组而言, stk 实际记录的 m 值应该加上每个子数组左边界 l 偏移
			m = partition(arr + l, r - l + 1) + l;
			if (m - 1 > l) {
				stk[p++] = l;
				stk[p++] = m - 1;
			}
			if (m + 1 < r) {
				stk[p++] = m + 1;
				stk[p++] = r;
			}
		}
	}
	free(stk);
}

void bubbleSort(int *arr, int size)
{
	int i, j;
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap<int>(arr[j], arr[j + 1]);
			}
		}
	}
}

void bubbleSort2(int *arr, int size)
{
	int i, j;
	int change = 1;
	for (int i = size - 1; i > 1 && change; i--) {
		change = 0;
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap<int>(arr[j], arr[j + 1]);
				change = 1;
			}
		}
	}
}

void AdjustDown(int *arr, int i, int len)
{
	int temp = arr[i];  // 暂存A[i]

	for (int k = 2 * i + 1; k < len; k = 2 * k + 1){ 
		// 调整节点，使子树根节点值最大（大根堆 ki >= k(2i）且 ki>= k(2i+1)）
		// k = 2 * i + 1、k = 2 * k + 1，即对应数组下标从 0 开始的调整
		if (k != len - 1 && arr[k + 1] > arr[k])
			++k;
		if (temp < arr[k]){
			arr[i] = arr[k];
			i = k;
		}
		else
			break;
	}
	arr[i] = temp;
}
void BuildMaxHeap(int *arr, int len)
{
	// 数组长度等于序列长度 len，第 0 元素对应建堆的序列第一项，因此 -1 对应数组下标
	for (int i = len / 2 - 1; i >= 0; --i) 
		AdjustDown(arr, i, len);
}
void HeapSort(int *arr, int n)
{
	BuildMaxHeap(arr, n);
	for (int i = n - 1; i>0; --i){
		swap<int>(arr[0], arr[i]);
		// 调整，把剩余的n-1个元素整理成堆
		AdjustDown(arr, 0, i);
	}
}

