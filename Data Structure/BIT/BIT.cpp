#include<bits/stdc++.h>
using namespace std;

template<class DT>
struct BIT { // 1- based indexing
	int n;
	std::vector<DT> fenwick;
	BIT() {}
	BIT(int _n) {
		n = _n;
		fenwick.assign(n + 1, 0);
	}
	DT query(int i) {
		DT ans = 0;
		for (; i >= 1; i -= (i & -i)) {
			ans += fenwick[i];
		}
		return ans;
	}
	void update(int i, DT val) {
		if (i <= 0) return ;
		for (; i <= n; i += (i & -i)) {
			fenwick[i] += val;
		}
	}
	void update(int b, int e, DT val) {
		update(b, val);
		update(e + 1, -val);
	}
	DT query(int b, int e) {
		return query(e) - query(b - 1);
	}
};
int main()
{
	;
}