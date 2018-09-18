#include "algo.h"
#include <stdio.h>
#include <string.h>
typedef struct tagPoint {
	int x, y;
}Point;

void test();
void test1();
void test2();
void test3();
void test4();

typedef char* charp;

int main()
{
	//test3();
	test4();
	getchar();
	return 0;
}

void test()
{
	const int N = 4;
	int i, j, k;
	//int **A = new int* [N]();
	//int **B = new int* [N]();
	int **C = new int*[N]();
	for (i = 0; i < N; i++) {
		//A[i] = new int[N]();
		//B[i] = new int[N]();
		C[i] = new int[N]();
	}
	int A[][4] = {
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4
	};

	int B[][4] = {
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4
	};

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i][j] = 0;
			for (k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%-5d", C[i][j]);
		}
		printf("\n");
	}
}

void test1()
{
	const int N = 5;
	int **m = new int*[N + 1]();
	int **s = new int*[N + 1]();
	for (int i = 0; i < N + 1; i++) {
		m[i] = new int[N + 1]();
		s[i] = new int[N + 1]();
	}
	int p[] = { 4, 5, 3, 6, 4, 5 };

	MatrixChain(p, N, m, s);
	printf("\n*************\ts\t*************\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%4d\t", s[i][j]);
		}
		printf("\n");
	}

	printf("\n*************\tm\t*************\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%4d\t", m[i][j]);
		}
		printf("\n");
	}
}

void test2()
{
	int **L = NULL;
	char x[] = { "ABCBDBBA" };
	char y[] = { "BDBCABAA" };
	int m = strlen(x);
	int n = strlen(y);
	printf("m = %d\nn = %d\n", m, n);
	printLCS(x, y, L, m, n);
	//printf("lcs = %d\n", longest2(x, y, m, n));
}

void test3()
{
	int n = 4;
	int ¦Ð[] = { -1,4,1,2,3 };
	int mns = getMNS(¦Ð, n);
	printf("mns = %d\n", mns);
}

void test4()
{
	int arr[] = { 16,7,3,20,17,8,15,1,5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	HeapSort(arr, n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}
