#include<bits/stdc++.h>
#define ll          long long
#define nl          '\n'
#define F           first
#define S           second
#define pb          push_back
#define all(a)      (a.begin()),(a.end())
#define Input       freopen("in.txt","r",stdin)
#define Output      freopen("out.txt","w",stdout)
#define PI          2*acos(0.0)
#define MOD         1000000007
using namespace std;


const int N = 2e5 + 5;

vector<int> z_function(string s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i < r) {
			z[i] = min(r - i, z[i - l]);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}




struct segtree
{
#define lft (node<<1)
#define rgt ((node<<1)|1)

	vector<ll> tree, lazy;
	segtree() {}
	segtree(int n) {
		tree.assign(4 * n, 0);
		lazy.assign(4 * n, 0);
	}

	inline void push(int node, int b, int e) {
		if (lazy[node] == 0) return ;
		tree[node] = tree[node] + (e - b + 1) * lazy[node];
		if (b != e)
		{
			lazy[lft] = lazy[lft] + lazy[node];
			lazy[rgt] = lazy[rgt] + lazy[node];
		}
		lazy[node] = 0;
	}

	inline ll merge(ll a, ll b) {
		return a + b;
	}

	void Update(int node, int b, int e, int i, int j, ll val) {
		push(node, b, e);
		if (i > e or j < b) return ;
		if (b >= i and e <= j) {
			lazy[node] += val;
			push(node, b, e);
			return ;
		}
		int mid = (b + e) >> 1;
		Update(lft, b, mid, i, j, val);
		Update(rgt, mid + 1, e, i, j, val);
		tree[node] = merge(tree[lft], tree[rgt]);
	}

	ll Query(int node, int b, int e, int i, int j) {
		push(node, b, e);
		if (j < b || i > e) return 0;
		if (b >= i && e <= j) {
			return tree[node];
		}
		int mid = (b + e) >> 1;
		return merge(Query(lft, b, mid, i, j), Query(rgt, mid + 1, e, i, j));
	}

};






void Solve()
{
	string s;
	cin >> s;
	int n = s.size();
	vector<int> z = z_function(s);
	z[0] = n;
	int ans = 0, mx = 0;
	segtree st(n + 5);
	vector<int> v;
	for (int i = n - 1; i >= 0; i--) {
		int len = n - i;
		if (z[i] == len) {
			v.push_back(len);
		}
		st.Update(1, 1, n, 1, z[i], 1);
	}
	cout << v.size() << nl;
	for (auto it : v) {
		cout << it << ' ' << st.Query(1, 1, n, it, it) << nl;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, T = 1;
	// cin >> T;
	for (t = 1; t <= T; t++)
		Solve();
	return 0;
}
