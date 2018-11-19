#include "algo.h"
#include <stdlib.h>
#include <stdio.h>
/* ����������С���� */
void MatrixChain(int *p, int n, int **m, int **s)
{
	int i, j;
	for (i = 1; i <= n; i++) m[i][i] = 0;
	for (int r = 2; r <= n; r++) {
		for (i = 1; i <= n - r + 1; i++) {
			j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++) {
				//Ai~Aj�ֳ�����2����(��m[i][k],��m[k+1][j]), //�ټ�������2���������˵Ĵ���(p[i-1] *p[k]*p[j])
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;//������С��,�����ŵĽ��
				}//if
			}//k
		} // i
	}// r
}

void matrixChain2(int *p, int n, int **m, int **s)
{
	for (int t = 1; t <= n; t++) m[t][t] = 0;
	for (int l = 2; l <= n; l++) { // ���������ȣ�����Ϊ2
		for (int i = 1; i <= n - l + 1; i++) { // ��ʼλ��
			int j = i + l - 1; // ��ֹλ��
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; // �������Ż��֣�˳�����Ľ����p���±��0��ʼ
			s[i][j] = i; // ��¼��ǰλ��
			for (int k = i + 1; k < j; k++) { // ����kΪ���ŵĻ���λ��
				int r = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; // ������
				if (r < m[i][j]) {  // �����ţ������
					m[i][j] = r;
					s[i][j] = k;
				}
			}
		}
	}
}

/* ����������У����Ӵ��� */
int longest(char *x, char *y, int m, int n, int ** &L)
{
	L = new int *[m + 1]();
	for (int i = 0; i <= m; i++) {
		L[i] = new int[n + 1]();
	}

	for (int i = 0; i <= m; i++) L[i][0] = 0;
	for (int j = 0; j <= n; j++) L[0][j] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;  // ע��L������x, y�±��Ӧ��ϵ
			else L[i][j] = L[i][j - 1] > L[i - 1][j] ? L[i][j - 1] : L[i - 1][j];
		}
	}
	int lcs = L[m][n];
	/*for (int i = 0; i <= m; i++) {
		delete[] L[i];
		L[i] = NULL;
	}
	delete [] L;
	L = NULL;*/
	return lcs;
}

/* �����L�����������1��ʼ����x, y�ַ�������±�֮�䣨��0��ʼ���Ķ�Ӧ��ϵ */
/* ��������������򣨲�ͬ�������ζ�Ӧ��� */
void printLCS(char *x, char *y, int m, int n, int **L)
{
	int lcs = longest(x, y, m, n, L);
	printf("lcs = %d\n", lcs);
	char *ret = new char[lcs + 1]();
	int i = m, j = n, k = lcs;
	do {
		/* �����ϻ�������õ������ս�����ܲ�һ�� */
		if (L[i][j] == L[i - 1][j]) // ����
			i--;
		else if (L[i][j] == L[i][j - 1]) // ����
			j--;

		else {
			ret[(k--) - 1] = x[i - 1]; // �����±��ϵ
			i--;
			j--;
		}
	} while (i > 0 && j > 0);
	printf("k = %d\n", k);
	printf("%s\n", ret + k);

	for (int i = 0; i <= m; i++) {
		delete[] L[i];
		L[i] = NULL;
	}
	delete[] L;
	L = NULL;
	delete[] ret;
}

/* ��ֻ�����������г��ȣ���ռ��Ͽ����Ż����ڼ���L[i][j]ʱ��ʵ����ֻ�õ�����L�ĵ�i�к͵�i-1�У�*/
int longest2(char *x, char *y, int m, int n)
{
	int m1 = 1;
	int **L = new int *[m1 + 1]();
	for (int i = 0; i <= m1; i++) {
		L[i] = new int[n + 1]();
	}

	for (int i = 0; i <= m1; i++) L[i][0] = 0;
	for (int j = 0; j <= n; j++) L[0][j] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1])
				L[1][j] += L[0][j - 1] + 1;
			else L[1][j] = L[1][j - 1] > L[0][j] ? L[1][j - 1] : L[0][j];
		}
	}
	int lcs = L[1][n];
	for (int i = 0; i <= m1; i++) {
		delete[] L[i];
		L[i] = NULL;
	}
	delete[] L;
	L = NULL;
	return lcs;
}


/* longest common substring */
#define MAX(x,y) ((x) >(y))?(x):(y)

int longest_sub(char *x, char *y, int m, int n, int ** &L)
{
    int lcs = 0;
    //int **L = new int *[m + 1]();
    //for (int i = 0; i <= m; i++) {
    //    L[i] = new int[n + 1]();
    //}

    for (int i = 0; i <= m; i++) L[i][0] = 0;
    for (int j = 0; j <= n; j++) L[0][j] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
                lcs = MAX(L[i][j], lcs);
            }
            else L[i][j] = 0;
        }
    }

    // for (int i = 0; i <= m; i++) {
    //     delete[] L[i];
    //     L[i] = NULL;
    // }
    // delete[] L;
    // L = NULL;

    return lcs;
}

void printLCS_sub(char *x, char *y, int m, int n, int **L)
{
    L = new int *[m + 1]();
    for (int i = 0; i <= m; i++) {
        L[i] = new int[n + 1]();
    }

    int lcs = longest_sub(x, y, m, n, L);
    printf("lcs = %d\n", lcs);
    char *ret = new char[lcs + 1]();
    int i = m, j = n, k = lcs;
    int flag = 0;
    for (i = m; i > 0; i--) {
        for (j = n; j > 0; j--) {
            if (L[i][j] == k) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) break;
    }

    printf("i = %d\t\tj = %d\n", i, j);
    for (int pos = i; pos >= 1; pos--)
        ret[(k--) - 1] = x[pos - 1];

    printf("lcs = %d\n", lcs);
    printf("%s\n", ret + k);

    for (int i = 0; i <= m; i++) {
        delete[] L[i];
        L[i] = NULL;
    }
    delete[] L;
    L = NULL;
    delete[] ret;
}


/* ��·���� */
int getMNS(int ��[], int n)
{
	// TODO(tangxuan): debug the code 

	int i = 0;
	int j = 0;
	int **Size = new int*[n + 1]();

	for (int k = 0; k <= n; k++) {
		Size[k] = new int[n + 1]();
	}

	for (j = 1; j <= ��[1] - 1; j++) {
		Size[1][j] = 0;
	}

	for (j = ��[1]; j < n; j++) {
		Size[1][j] = 1;
	}

	for (i = 2; i < n; i++) {
		for (j = 1; j <= ��[i] - 1; j++) {
			Size[i][j] = Size[i - 1][j] + 1;
		}
	}

	for (j = ��[i]; j < n; j++) {
		Size[i][j] = Size[i - 1][j] > Size[i - 1][��[i] - 1] + 1 ? Size[i - 1][j] : Size[i - 1][��[i] - 1] + 1;
	}

	int mns = Size[n][n] = Size[n - 1][n] > Size[n - 1][��[n] - 1] + 1 ? Size[n - 1][n] : Size[n - 1][��[n] - 1] + 1;

	for (int k = 0; k <= n; k++) {
		delete[] Size[k];
		Size[k] = NULL;
	}
	delete[] Size;
	Size = NULL;

	return mns;
}

/* �����ظ��ļ���������ĸ���ֵ��ַ� */
char *filter(char *str, int len)
{
    char *cp = str;
    int flags[10 + 26 + 26] = { 0 };
    int len1 = 10;
    int len2 = 26;
    int len3 = 26;

    while (*cp != '\0') {
        if (*cp >= '0' && *cp <= '9') {
            flags[*cp - '0'] = 1;
        }
        if (*cp >= 'A' && *cp <= 'Z') {
            flags[*cp - 'A' + len1] = 1;
        }
        if (*cp >= 'a' && *cp <= 'z') {
            flags[*cp - 'a' + len1 + len2] = 1;
        }
        cp++;
    }

    char *ret = new char[len + 1]();
    int i = 0;
    int k = 0;
    while (i < len1 + len2 + len3) {
        if (flags[i] == 1) {
            if (i < len1)
                ret[k++] = i + '0';
            else if (len1 <= i && i < len1 + len2)
                ret[k++] = i + 'A' - len1;
            else if (len1 + len2 <= i && i < len1 + len2 + len3)
                ret[k++] = i + 'a' - len2 - len1;
            else
                ;
        }
        ++i;
    }
    ;
    return ret;
}

