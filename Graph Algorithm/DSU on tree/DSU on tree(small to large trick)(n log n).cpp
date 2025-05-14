#include<bits/stdc++.h>
#define ll                  long long
#define nl                  '\n'
#define F                   first
#define S                   second
#define pb		    		push_back
#define all(a)              (a.begin()),(a.end())
#define UNIQUE(X)           (X).erase(unique(all(X)),(X).end())
#define SORT_UNIQUE(c)      (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define ms(a,b)             memset(a, b, sizeof(a))
#define Input               freopen("in.txt","r",stdin)
#define Output              freopen("out.txt","w",stdout)
#define MOD                 1000000007
using namespace std;


const int N = 2e5 + 5;

int n, col[N], sz[N], cnt[N], mxcol = 0;
ll sum[N], res[N];
std::vector<int> graph[N], vec[N];

void DFS_size(int u, int p)
{
	sz[u] = 1;
	for (auto v : graph[u]) {
		if (v != p) {
			DFS_size(v, u);
			sz[u] += sz[v];
		}
	}
}

void DFS(int u, int p = 0, bool keep = 0)
{
	int mx = -1, bigchild = -1;
	for (auto v : graph[u]) {
		if (v != p && mx < sz[v])
		{
			mx = sz[v];
			bigchild = v;
		}
	}
	for (auto v : graph[u]) {
		if (v != p && v != bigchild) {
			DFS(v, u, 0);
		}
	}
	if (bigchild != -1)
	{
		DFS(bigchild, u, 1);
		swap(vec[bigchild], vec[u]);
	}
	vec[u].push_back(u);

	cnt[col[u]]++;
	sum[cnt[col[u]]] += col[u];
	if (cnt[col[u]] > mxcol) {
		mxcol++;
	}

	for (auto v : graph[u])
	{
		if (v != p && v != bigchild)
		{
			for (auto x : vec[v]) {
				vec[u].push_back(x);
				cnt[col[x]]++;
				sum[cnt[col[x]]] += col[x];
				if (cnt[col[x]] > mxcol) {
					mxcol++;
				}
			}
		}
	}
	res[u] = sum[mxcol];
	if (keep == 0) {
		for (auto v : vec[u]) {
			sum[cnt[col[v]]] -= col[v];
			cnt[col[v]]--;
			if (cnt[col[v]] < mxcol) {
				mxcol--;
			}
		}
	}

}
void Solve(int t)
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> col[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	DFS_size(1, 0);
	DFS(1, 0, 0);
	for (int i = 1; i <= n; i++) {
		cout << res[i] << " \n"[i == n];
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

