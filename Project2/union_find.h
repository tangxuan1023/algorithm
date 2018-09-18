
#ifndef __DISJOINT_SET_H__
#define __DISJOINT_SET_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int rank;
	int p;
	int size;
} uni_elt;

class Universe {
public:
	Universe(int elements) {
		elts = new uni_elt[elements];
		num = elements;
		for (int i = 0; i < elements; i++) {
			elts[i].rank = 0;
			elts[i].size = 1;
			elts[i].p = i;
		}
	}

	~Universe() {
		delete[] elts;
	}

	int find(int x) {
		int y = x;
		while (y != elts[y].p)
			y = elts[y].p;
		elts[x].p = y;
		return y;
	}

	void join(int x, int y) {
		if (elts[x].rank > elts[y].rank) {
			elts[y].p = x;
			elts[x].size += elts[y].size;
		}
		else {
			elts[x].p = y;
			elts[y].size += elts[x].size;
			if (elts[x].rank == elts[y].rank)
				elts[y].rank++;
		}
		num--;
	}

	int size(int x) const {
		return elts[x].size;
	}

	int num_sets() const {
		return num;
	}

private:
	uni_elt *elts;
	int num;
};

#endif