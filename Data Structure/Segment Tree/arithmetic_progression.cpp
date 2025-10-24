#include<bits/stdc++.h>
#define ll                  long long
#define endl                '\n'
#define sz                  200005
using namespace std;

const int N = 200005;

struct item {
	ll a, d;
	bool operator == (const item & p) const {
		return a == p.a && d == p.d;
	}
};


int n, m;

struct segtree
{
#define lft (node<<1)
#define rgt ((node<<1)|1)

	ll tree[4 * N];
	item lazy[4 * N];
	segtree() {
		for (int i = 0; i < 4 * N; i++)
		{
			lazy[i] = {0, 0};
			tree[i] = 0;
		}
	}

	item NEUTRAL_VALUE = {0, 0};

	ll merge(ll a, ll b) {
		return a + b;
	}

	void push(ll node, ll b, ll e)
	{
		if (lazy[node] == NEUTRAL_VALUE) return ;
		ll len = (e - b + 1);
		tree[node] += len * (2LL * lazy[node].a + (len - 1) * lazy[node].d) / 2LL;
		if (b != e)
		{
			lazy[lft] = {lazy[node].a + lazy[lft].a, lazy[node].d + lazy[lft].d};
			ll mid = (b + e) >> 1;
			lazy[rgt] = {lazy[rgt].a + lazy[node].a + (mid + 1 - b)*lazy[node].d , lazy[rgt].d + lazy[node].d};
		}
		lazy[node] = NEUTRAL_VALUE;
	}


	void Update(ll node, ll b, ll e, ll i, ll j, ll a, ll d) {
		push(node, b,  e);
		if (j < b || i > e) return ;
		if (b >= i && e <= j) {
			lazy[node] = {a + (b - i)*d, d}; // set lazy
			push(node, b, e);
			return ;
		}
		ll mid = (b + e) >> 1;
		Update(lft, b, mid, i, j, a, d);
		Update(rgt, mid + 1, e, i, j, a, d);
		tree[node] = merge(tree[lft], tree[rgt]);
	}

	void Update(ll i, ll j, ll a, ll d)
	{
		return Update(1, 1, n, i, j, a, d);
	}

	ll Query(ll node, ll b, ll e, ll i) {
		push(node, b, e);
		if (i < b || i > e) return 0LL;
		if (b == e) {
			return tree[node];
		}
		ll mid = (b + e) >> 1;
		ll p = Query(lft, b, mid, i);
		ll q = Query(rgt, mid + 1, e, i);
		return merge(p, q);
	}

	ll Query(ll i)	{
		return Query(1, 1, n, i);
	}
};


void Solve(int t)
{
	cin >> n >> m;

	segtree st;

	while (m--)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			ll l, r, a, d;
			cin >> l >> r >> a >> d;
			st.Update(l, r, a, d);
		}
		else {
			int i;
			cin >> i;
			cout << st.Query(i) << endl;
		}
	}
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