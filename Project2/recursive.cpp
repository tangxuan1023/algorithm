#include "algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binarySearch(int *arr, int size, int key)
{
	int low = 0;
	int high = size - 1;
	while (high >= low) {
		//int mid = (low + high) / 2;
        int mid = low + (high - low) / 2; // 当high和low同时为很大的数时，计算 high + low 会发生整数溢出的情况
		if (arr[mid] == key) return mid;
		else if (arr[mid] > key) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}

int binarySearch2(int *arr, int low, int high, int key)
{
	if (low > high) return -1;
	//int mid = (low + high) >> 1;
    int mid = low + ((high - low) >> 1);
	if (arr[mid] == key) return mid;
	else if (arr[mid] > key) return binarySearch2(arr, low, mid - 1, key);
	else return binarySearch2(arr, mid + 1, high, key);
}


int factorial(int n)
{
#if 1
	if (n == 0) {
		return 1;
	}
	return n * factorial(n - 1);
#else
	int ret = 1;
	int i = 1;
	while (i <= n) {
		ret *= i;
		i++;
	}
	return ret;
#endif
}


int fibonacci(int n)
{
#if 1
	if (n < 2) {
		return n;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
#else
	int cur = 1;
	int pre = 1;
	int nex = 1;
	int i = 1;
	while (i <= n) {
		pre = cur;
		cur = nex;
		nex = cur + pre;
		i++;
	}
	return pre;
#endif
}

static int AdditiveSequence(int n, int t0, int t1)
{
	if (n == 0) return t0;
	//if (n == 1) return t1;
	return AdditiveSequence(n - 1, t1, t0 + t1);
}

int fibonacci2(int n)
{
	return AdditiveSequence(n, 0, 1);
}

// reverse string
char *reverse_(char *str, int l, int r)
{
	if (r <= l) return str;
	char ch = str[r];
	str[r] = str[l];
	str[l] = ch;
	return reverse_(str, l + 1, r - 1);
}

#if 0
char *reverse(char *str)
{
	return reverse_(str, 0, strlen(str) - 1);
}
#endif

char *reverse(char *s)
{
	register char t, *p = s,
		*q = (s + (strlen(s) - 1));

	while (p < q) {
		t = *p;
		*p++ = *q;
		*q-- = t;
	}

	return s;
}

// Character arrangement
static void exchangeChar(char *str, int pos1, int pos2)
{
	/*char ch = str[pos1];
	str[pos1] = str[pos2];
	str[pos2] = ch;*/
	swap<char>(str[pos1], str[pos2]);
}

static void RecurPermu(char *str, int k)
{
	int len = strlen(str);
	if (k == len) {
		printf("%s\n", str);
	}
	else {
		for (int i = k; i < len; i++) {
			exchangeChar(str, k, i);
			RecurPermu(str, k + 1);
			exchangeChar(str, k, i);
		}
	}
}

void ListPermu(char *str)
{
	RecurPermu(str, 0);
}