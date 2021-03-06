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
    if (size <= 1) return 0;
    int key = arr[0];
    int i = 1;
    int j = size - 1;

    for (;;) {
        while (arr[j] < key) j--; // 升降序控制
        while (arr[i] >= key && i < size) i++; // 升降序控制
        if (i >= j) break;
        swap<int>(arr[i], arr[j]);
        i++; j--;  // 每两对数判断完成后，需要更新下标索引
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
    // 通过记录子数组左右边界来实现递归分解
    stk[p++] = 0;
    stk[p++] = size - 1;
    m = 0;
    while (p != 0) {
        r = stk[--p];
        l = stk[--p];
        if (l < r) {
            // 注意，对子数组的划分得到的基准位置 m 的值是相对于子数组偏移的，
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

void partition3(int arr[], int l, int h, int *pl, int *ph)
{
    int size = h - l + 1;
    if (h - l <= 1) // 两个元素
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
    /* TODO: 对于测试用例 arr[] = { 0, 2, 1, 2, 0, 1, 0, 0, 2, 1, 2, 1};
    一次划分之后数组已经有序，所以最好的做法是先判断各分区元素，
    并且只有分区内元素互不相同时才做递归调用
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
    二叉树形式表示的堆逻辑结构
              3
            /   \
          2       6
         / \     / \
        7   5   1   4
       /
      8

    数组形式存储堆结构 array[] = { 3, 2, 6, 7, 5, 1, 4, 8 };
    对比堆的逻辑结构，数组元素间存在一下关系，下标从0开始
        parent(i) = (i - 1) / 2;
        left(i)   = (2 * i + 1);
        right(i)  = (2 * i + 2); // left(i) + 1
*/

/* 大根堆排序实现，升序 */
void AdjustDown(int *arr, int i, int len)
{
    int temp = arr[i];  // 暂存A[i]

    for (int k = 2 * i + 1/*某根节点的左子节点，参见前注释*/; k < len; k = 2 * k + 1 /*下一子树的左子节点*/) {
        if (k != len - 1 && arr[k + 1]/*右子节点*/ > arr[k]/*左子节点*/)
            ++k;  // 右节点值大于左节点，取右子节点为最大
        if (temp < arr[k]) { // 比较子节点的最大值和根节点值的大小
                            // 如果根节点值不是最大，则交换最大值到根节点
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
    // 数组长度等于序列长度 len，数组前半段存储各子树的根节点(非叶节点)，参见前注释
    // 第 0 元素对应建堆的序列第一项，因此 -1 对应数组下标
    for (int i = len / 2 - 1; i >= 0; --i)
        AdjustDown(arr, i, len);
}

void HeapSort(int *arr, int n)
{
    BuildMaxHeap(arr, n);
    for (int i = n - 1; i > 0; --i) {
        swap<int>(arr[0], arr[i]);
        // 调整，把剩余的n-1个元素整理成堆
        AdjustDown(arr, 0, i);
    }
}

void gnomeSort(int arr[], int n)
{
    int index = 0;

    while (index < n) {
        if (index == 0)  // 初始情况下，向前一步
            index++;
        if (arr[index] >= arr[index - 1]) // 如果两数顺序正确，向前一步
            index++;
        else {  // 顺序不正确，交换两数，并后退一步
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return;
}

