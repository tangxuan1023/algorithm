#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//sort algorithm

void selectSort(int *arr, int size)
{
	int i, j, min;  // min Ϊ��ǰ��С�����±�
	for (i = 0; i < size; i++) { // ѡ����ڵ� i ��λ�õ���
		min = i;  // ���赱ǰλ�õ�����С
		for (j = i + 1; j < size; j++) { // ����������������Ƿ��и�С��
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap<int>(arr[i], arr[min]); // ��Ŀǰ��С������������ǰλ�ã���ǰλ����ǰ����������
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
	mergeSort(arr2, size2);  // �ݹ�ʹ�ò������ܻ����ջ���������
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
		while (arr[j] < key) j--; // ���������
		//do i++; while (i <= high && arr[i] < key);
		while (i < size && arr[i] > key) i++; // ���������
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
	// ͨ����¼���������ұ߽���ʵ�ֵݹ�ֽ�
	stk[p++] = 0;
	stk[p++] = size - 1;
	m = 0;
	while (p != 0) {
		r = stk[--p];
		l = stk[--p];
		if (l < r) {
			// ע�⣬��������Ļ��ֵõ��� ��׼λ�� m ��ֵ�������������ƫ�Ƶģ�
			// �������ԭʼ�������, stk ʵ�ʼ�¼�� m ֵӦ�ü���ÿ����������߽� l ƫ��
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
	int temp = arr[i];  // �ݴ�A[i]

	for (int k = 2 * i + 1; k < len; k = 2 * k + 1){ 
		// �����ڵ㣬ʹ�������ڵ�ֵ��󣨴���� ki >= k(2i���� ki>= k(2i+1)��
		// k = 2 * i + 1��k = 2 * k + 1������Ӧ�����±�� 0 ��ʼ�ĵ���
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
	// ���鳤�ȵ������г��� len���� 0 Ԫ�ض�Ӧ���ѵ����е�һ���� -1 ��Ӧ�����±�
	for (int i = len / 2 - 1; i >= 0; --i) 
		AdjustDown(arr, i, len);
}
void HeapSort(int *arr, int n)
{
	BuildMaxHeap(arr, n);
	for (int i = n - 1; i>0; --i){
		swap<int>(arr[0], arr[i]);
		// ��������ʣ���n-1��Ԫ������ɶ�
		AdjustDown(arr, 0, i);
	}
}

