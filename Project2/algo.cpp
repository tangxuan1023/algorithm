#include "algo.h"
#include <stdlib.h>
#include <stdio.h>
/* 矩阵连乘最小次数 */
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
				//Ai~Aj分成左右2部分(左m[i][k],右m[k+1][j]), //再加上左右2部分最后相乘的次数(p[i-1] *p[k]*p[j])
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;//保存最小的,即最优的结果
				}//if
			}//k
		} // i
	}// r
}

void matrixChain2(int *p, int n, int **m, int **s)
{
	for (int t = 1; t <= n; t++) m[t][t] = 0;
	for (int l = 2; l <= n; l++) { // 矩阵链长度，至少为2
		for (int i = 1; i <= n - l + 1; i++) { // 起始位置
			int j = i + l - 1; // 终止位置
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; // 不作最优划分，顺序计算的结果，p的下标从0开始
			s[i][j] = i; // 记录当前位置
			for (int k = i + 1; k < j; k++) { // 假设k为更优的划分位置
				int r = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; // 计算结果
				if (r < m[i][j]) {  // 若更优，则更新
					m[i][j] = r;
					s[i][j] = k;
				}
			}
		}
	}
}

/* 最长公共子序列（非子串） */
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
			if (x[i - 1] == y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;  // 注意L索引和x, y下标对应关系
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

/* 处理好L表格索引（由1开始）和x, y字符数组的下标之间（由0开始）的对应关系 */
/* 最长子序列搜索方向（不同结果）如何对应设计 */
void printLCS(char *x, char *y, int m, int n, int **L)
{
	int lcs = longest(x, y, m, n, L);
	printf("lcs = %d\n", lcs);
	char *ret = new char[lcs + 1]();
	int i = m, j = n, k = lcs;
	do {
		/* 先往上还是往左得到的最终结果可能不一样 */
		if (L[i][j] == L[i - 1][j]) // 往上
			i--;
		else if (L[i][j] == L[i][j - 1]) // 往左
			j--;

		else {
			ret[(k--) - 1] = x[i - 1]; // 处理下标关系
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

/* 若只需计算最长子序列长度，则空间上可以优化（在计算L[i][j]时，实际上只用到数组L的第i行和第i-1行）*/
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


/* 电路布线 */
int getMNS(int π[], int n)
{
	// TODO(tangxuan): debug the code 

	int i = 0;
	int j = 0;
	int **Size = new int*[n + 1]();

	for (int k = 0; k <= n; k++) {
		Size[k] = new int[n + 1]();
	}

	for (j = 1; j <= π[1] - 1; j++) {
		Size[1][j] = 0;
	}

	for (j = π[1]; j < n; j++) {
		Size[1][j] = 1;
	}

	for (i = 2; i < n; i++) {
		for (j = 1; j <= π[i] - 1; j++) {
			Size[i][j] = Size[i - 1][j] + 1;
		}
	}

	for (j = π[i]; j < n; j++) {
		Size[i][j] = Size[i - 1][j] > Size[i - 1][π[i] - 1] + 1 ? Size[i - 1][j] : Size[i - 1][π[i] - 1] + 1;
	}

	int mns = Size[n][n] = Size[n - 1][n] > Size[n - 1][π[n] - 1] + 1 ? Size[n - 1][n] : Size[n - 1][π[n] - 1] + 1;

	for (int k = 0; k <= n; k++) {
		delete[] Size[k];
		Size[k] = NULL;
	}
	delete[] Size;
	Size = NULL;

	return mns;
}

/* 过滤重复的及其他非字母数字的字符 */
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

