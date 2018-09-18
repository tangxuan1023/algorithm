#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

template<typename T> void swap(T &a, T&b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int binarySearch(int *arr, int size, int key);
int binarySearch2(int *arr, int low, int high, int key);
int factorial(int n);
int fibonacci(int n);
int fibonacci2(int n);

char *reverse(char *str);
void ListPermu(char *str);

void bubbleSort(int *arr, int size);
void bubbleSort2(int *arr, int size);
void selectSort(int *arr, int size);
void  mergeSort(int *arr, int size);
void  quickSort(int *arr, int high);
void quick_sort(int *arr, int high);
void HeapSort(int *arr, int n);

void MatrixChain(int *p, int n, int **m, int **s);
int longest(char *x, char *y, int m, int n, int **&L);
void printLCS(char *x, char *y, int **L, int m, int n);

int longest2(char *x, char *y, int m, int n);

int getMNS(int ¦Ð[], int n);

#endif
