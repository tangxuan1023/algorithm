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
    if (size <= 1) return 0;
    int key = arr[0];
    int i = 1;
    int j = size - 1;

    for (;;) {
        while (arr[j] < key) j--; // ���������
        while (arr[i] >= key && i < size) i++; // ���������
        if (i >= j) break;
        swap<int>(arr[i], arr[j]);
        i++; j--;  // ÿ�������ж���ɺ���Ҫ�����±�����
    }

    swap<int>(arr[0], arr[j]);
    return j;
}

int partition1(int arr[], int l, int h)
{
    int x = arr[l];
    int i = l + 1;
    int j = h;
    while (1)
    {
        while (arr[j] > x)j--;
        while (arr[i] <= x)i++;
        if (i >= j) break;
        swap<int>(arr[i], arr[j]);
    }

    swap<int>(arr[l], arr[j]);
    return j;
}

int partition2(int arr[], int l, int h)
{
    int x = arr[h];
    int i = l - 1;
    for (int j = l; j < h; j++)
    {
        if (arr[j] <= x)
        {
            i += 1;
            swap<int>(arr[i], arr[j]);
        }
    }

    swap<int>(arr[i + 1], arr[h]);
    return i + 1;
}

void quickSort(int *arr, int size)
{
    if (size <= 1) return;
    int pos = partition(arr, size);
    quickSort(arr, pos);
    quickSort(arr + pos + 1, size - pos - 1);
}

void qsort(int arr[], int l, int h)
{
    if (h - l < 1) return;
    int p = partition1(arr, l, h);
    //int p = partition2(arr, l, h);
    printf("partition:%d\n", p);
    qsort(arr, l, p - 1);
    qsort(arr, p + 1, h);
}

void quick_sort(int *arr, int size)
{
    if (size <= 1) return;
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
            // ע�⣬��������Ļ��ֵõ��Ļ�׼λ�� m ��ֵ�������������ƫ�Ƶģ�
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

void partition3(int arr[], int l, int h, int *pl, int *ph)
{
    int size = h - l + 1;
    if (h - l <= 1) // ����Ԫ��
    {
        if (arr[l] >= arr[h])
            swap<int>(arr[l], arr[h]);
        *pl = l;
        *ph = h;
        return;
    }

    int x = arr[h];
    int mid = l;

    while (mid <= h)
    {
        if (arr[mid] < x)
        {
            swap<int>(arr[l++], arr[mid++]);
        }
        else if (arr[mid] == x)
        {
            mid++;
        }
        else if (arr[mid] > x)
        {
            swap<int>(arr[h--], arr[mid]);
        }
    }

    *pl = l - 1;
    *ph = mid - 1;  // or *ph = h;

    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}

void qsort3(int arr[], int l, int h)
{
    if (h - l <= 0) return;
    int i = 0;
    int j = 0;
    partition3(arr, l, h, &i, &j);
    /* TODO: ���ڲ������� arr[] = { 0, 2, 1, 2, 0, 1, 0, 0, 2, 1, 2, 1};
    һ�λ���֮�������Ѿ�����������õ����������жϸ�����Ԫ�أ�
    ����ֻ�з�����Ԫ�ػ�����ͬʱ�����ݹ����
    */
    //printf("l:%d, h:%d\n", i, j);
    qsort3(arr, l, i);
    qsort3(arr, j, h);
}

void bubbleSort(int *arr, int size)
{
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

/**
    ��������ʽ��ʾ�Ķ��߼��ṹ
              3
            /   \
          2       6
         / \     / \
        7   5   1   4
       /
      8

    ������ʽ�洢�ѽṹ array[] = { 3, 2, 6, 7, 5, 1, 4, 8 };
    �Աȶѵ��߼��ṹ������Ԫ�ؼ����һ�¹�ϵ���±��0��ʼ
        parent(i) = (i - 1) / 2;
        left(i)   = (2 * i + 1);
        right(i)  = (2 * i + 2); // left(i) + 1
*/

/* ���������ʵ�֣����� */
void AdjustDown(int *arr, int i, int len)
{
    int temp = arr[i];  // �ݴ�A[i]

    for (int k = 2 * i + 1/*ĳ���ڵ�����ӽڵ㣬�μ�ǰע��*/; k < len; k = 2 * k + 1 /*��һ���������ӽڵ�*/) {
        if (k != len - 1 && arr[k + 1]/*���ӽڵ�*/ > arr[k]/*���ӽڵ�*/)
            ++k;  // �ҽڵ�ֵ������ڵ㣬ȡ���ӽڵ�Ϊ���
        if (temp < arr[k]) { // �Ƚ��ӽڵ�����ֵ�͸��ڵ�ֵ�Ĵ�С
                            // ������ڵ�ֵ��������򽻻����ֵ�����ڵ�
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
    // ���鳤�ȵ������г��� len������ǰ��δ洢�������ĸ��ڵ�(��Ҷ�ڵ�)���μ�ǰע��
    // �� 0 Ԫ�ض�Ӧ���ѵ����е�һ���� -1 ��Ӧ�����±�
    for (int i = len / 2 - 1; i >= 0; --i)
        AdjustDown(arr, i, len);
}

void HeapSort(int *arr, int n)
{
    BuildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; --i) {
        swap<int>(arr[0], arr[i]);
        // ��������ʣ���n-1��Ԫ������ɶ�
        AdjustDown(arr, 0, i);
    }
}

void gnomeSort(int arr[], int n)
{
    int index = 0;

    while (index < n) {
        if (index == 0)  // ��ʼ����£���ǰһ��
            index++;
        if (arr[index] >= arr[index - 1]) // �������˳����ȷ����ǰһ��
            index++;
        else {  // ˳����ȷ������������������һ��
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return;
}

