#include "branch_limit.h"
#include <iostream>

using namespace std;

int branch_limit_main()
{
	double c = 30;
	int n = 4;
	double *p = new double[5];
	p[0] = 0; p[1] = 45; p[2] = 25; p[3] = 25; p[4] = 30;

	double *w = new double[5];
	w[0] = 0; w[1] = 16; w[2] = 15; w[3] = 15; w[4] = 15;

	int *x = new int[5];
	BackPack bp;
	double m = bp.knapsack(p, w, c, x);

	cout << "*****0-1*****" << endl;
	cout << "n=" << n << endl;
	cout << "c=" << c << endl;
	cout << "w= {" << w[1] << " " << w[2] << " " << w[3] << " " << w[4] << "}" << endl;
	cout << "v= {" << p[1] << " " << p[2] << " " << p[3] << " " << p[4] << "}" << endl;
	cout << "best=" << m << endl;
	cout << "select:";
	for (int i = 1; i <= n; i++)
		cout << x[i] << " ";
	cout << endl;
	return 0;
}