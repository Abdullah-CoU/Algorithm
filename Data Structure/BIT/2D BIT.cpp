#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
typedef int DT;

// template<class DT>
struct BIT { // 1- based indexing
	int n;
	int fenwick[N][N];
	BIT() {
		memset(fenwick, 0, sizeof(fenwick));
	}
	DT query(int x, int y) {
		DT ans = 0;
		for (; x >= 1; x -= (x & -x)) {
			for (int j = y; j >= 1; j -= (j & -j)) {
				ans += fenwick[x][j];
			}
		}
		return ans;
	}
	void update(int x, int y, DT val) {
		if (x <= 0 || y <= 0) return ;
		for (; x < N; x += (x & -x)) {
			for (int j = y; j < N; j += (j & -j)) {
				fenwick[x][j] += val;
			}
		}
	}
	void update(int x1, int y1, int x2, int y2, DT val) {
		update(x1, y1, val);
		update(x1, y2 + 1, -val);
		update(x2 + 1, y1, -val);
		update(x2 + 1, y2 + 1, val);
	}
	DT query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
	}
};
int main()
{
	;
}