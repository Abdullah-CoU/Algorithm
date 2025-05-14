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


const int N = 1e5 + 5;

int n, m, sz[N], cnt[N], level[N], res[N], parent[20][N];
std::vector<int> graph[N], vec[N];
vector<pair<int, int>> query[N];

void DFS_size(int v, int p) {
	parent[0][v] = p;
	for (int i = 1; i <= 17; i++) {
		parent[i][v] = parent[i - 1][parent[i - 1][v]];
	}
	sz[v] = 1;
	level[v] = level[p] + 1;
	for (auto u : graph[v]) {
		if (u != p) {
			DFS_size(u, v);
			sz[v] += sz[u];
		}
	}
}

int kth_parent(int u, int k)
{
	for (int i = 17; i >= 0; i--)
	{
		if ((1 << i) <= k)
		{
			u = parent[i][u];
			k -= (1 << i);
		}
	}
	return u;
}


void DFS(int v, int p = 0, bool keep = 0) {
	int Max = -1, bigchild = -1;
	for (auto u : graph[v]) {
		if (u != p && Max < sz[u]) {
			Max = sz[u];
			bigchild = u;
		}
	}
	for (auto u : graph[v]) {
		if (u != p && u != bigchild) {
			DFS(u, v, 0);
		}
	}
	if (bigchild != -1) {
		DFS(bigchild, v, 1);
		swap(vec[v], vec[bigchild]);
	}
	vec[v].push_back(v);

	cnt[level[v]]++;
	for (auto u : graph[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				cnt[level[x]]++;
				vec[v].push_back(x);
			}
		}
	}
	for (auto [l, id] : query[v]) {
		res[id] = cnt[level[v] + l] - 1;
	}
	if (keep == 0) {
		for (auto u : vec[v]) {
			cnt[level[u]]--;
		}
	}

}
void Solve(int t)
{
	cin >> n;

	vector<int> root;
	for (int i = 1; i <= n; i++)
	{
		int p;	cin >> p;
		if (p == 0) {
			root.push_back(i);
		}
		else {
			graph[p].push_back(i);
			graph[i].push_back(p);
		}
	}

	for (auto v : root) {
		DFS_size(v, 0);
	}


	int q; cin >> q;
	for (int i = 1; i <= q; i++) {
		int v, p;
		cin >> v >> p;
		// cout << kth_parent(v, p) << endl;
		query[kth_parent(v, p)].push_back({p, i});
	}

	for (auto v : root) {
		DFS(v);
	}
	for (int i = 1; i <= q; i++) {
		cout << res[i] << " \n"[i == q];
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

