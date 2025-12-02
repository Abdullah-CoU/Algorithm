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
		tree[node] = tree[node] +  lazy[node];
		if (b != e)
		{
			lazy[lft] = lazy[lft] + lazy[node];
			lazy[rgt] = lazy[rgt] + lazy[node];
		}
		lazy[node] = 0;
	}

	inline ll merge(ll a, ll b) {
		return min(a, b);
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
		tree[node] = min(tree[lft], tree[rgt]);
	}

	ll Query(int node, int b, int e, int i, int j) {
		push(node, b, e);
		if (j < b || i > e) return 1e15;
		if (b >= i && e <= j) {
			return tree[node];
		}
		int mid = (b + e) >> 1;
		return min(Query(lft, b, mid, i, j), Query(rgt, mid + 1, e, i, j));
	}

};


int type[N], height[N], n, leftmost[N];

ll dp[N];
// helper[j] = helper[j-1] + rmax(j,i)
void Solve()
{
	cin >> n;
	map<int, int> m;
	leftmost[0] = 1;
	for (int i = 1; i <= n; i++) {
		cin >> type[i] >> height[i];
		leftmost[i] = leftmost[i - 1];
		leftmost[i] = max(leftmost[i], m[type[i]] + 1);
		m[type[i]] = i;
	}

	// for (int i = 1; i <= n; i++) {
	// 	cout << leftmost[i] << " \n"[i == n];
	// }

	stack<int> s;
	s.push(0);
	segtree st(n + 2);

	for (int i = 1; i <= n; i++) {
		while (s.size() > 1 and height[s.top()] <= height[i]) {
			int curpos = s.top();
			s.pop();
			int prevpos = s.top();
			st.Update(1, 1, n, prevpos + 1, curpos, -height[curpos]);
		}
		st.Update(1, 1, n, s.top() + 1, i, height[i]);

		s.push(i);

		dp[i] = st.Query(1, 1, n, leftmost[i], i);
		st.Update(1, 1, n, i + 1, i + 1, dp[i]);

	}

	cout << dp[n] << nl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, T = 1;
	cin >> T;
	for (t = 1; t <= T; t++) {
		cout << "Case " << t << ": ";
		Solve();
	}
	return 0;
}
