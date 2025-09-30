#include<bits/stdc++.h>
#define ll                  long long
#define endl                '\n'
#define F                   first
#define S                   second
#define all(a)              (a.begin()),(a.end())
#define UNIQUE(X)           (X).erase(unique(all(X)),(X).end())
#define SORT_UNIQUE(c)      (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define ms(a,b)             memset(a, b, sizeof(a))
#define Input               freopen("in.txt","r",stdin)
#define Output              freopen("out.txt","w",stdout)
#define MOD                 1000000007
#define sz                  200005
using namespace std;

const int N = 200005;
typedef int item;


item a[N];


struct segtree
{
#define lft (node<<1)
#define rgt ((node<<1)|1)

	item tree[4 * N];

	item NEUTRAL_VALUE = 0;
	item single(item v) {
		return v;
	}
	item merge(item a, item b) {
		return a + b;
	}

	void Build(int node, int b, int e) {
		if (b == e) {
			tree[node] = a[b];
			return ;
		}
		int mid = (b + e) >> 1;
		Build(lft, b, mid);
		Build(rgt, mid + 1, e);
		tree[node] = merge(tree[lft], tree[rgt]);
	}

	void Update(int node, int b, int e, int i, int x) {
		if (i < b || i > e) return ;
		if (b == e && b == i) {
			tree[node] = x;
			return ;
		}
		int mid = (b + e) >> 1;
		Update(lft, b, mid, i, x);
		Update(rgt, mid + 1, e, i, x);
		tree[node] = merge(tree[lft], tree[rgt]);
	}

	item Query(int node, int b, int e, int i, int j) {
		if (j < b || i > e) return NEUTRAL_VALUE;
		if (b >= i && e <= j) {
			return tree[node];
		}
		int mid = (b + e) >> 1;
		item p = Query(lft, b, mid, i, j);
		item q = Query(rgt, mid + 1, e, i, j);
		return merge(p, q);
	}

};


void Solve(int t)
{
	;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, T = 1;
	// cin >> T;
	for (t = 1; t <= T; t++)
		Solve(t);
	return 0;
}

