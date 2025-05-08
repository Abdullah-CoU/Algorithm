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

int n, c[N], val[N], ans[N], par[N];
std::vector<int> graph[N];
set<int> st[N];

void MakeSet(int n)
{
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		st[i].clear();
	}
}
int FindPar(int u)
{
	if (par[u] == u)
		return u;
	return par[u] = FindPar(par[u]);
}
void Union(int u, int v)
{
	int parU = FindPar(u);
	int parV = FindPar(v);
	if (parU != parV)
	{
		par[parU] = parV;
	}
}
void merge(int u, int v)
{
	int parU = FindPar(u);
	int parV = FindPar(v);
	if (parU == parV)
		return ;
	if (st[parU].size() > st[parV].size())
		swap(parU, parV);
	Union(parU, parV);
	for (auto it : st[parU]) {
		st[parV].insert(it);
	}
	st[parU].clear();
}

void DFS(int u, int par)
{
	for (auto v : graph[u]) {
		if (v != par) {
			DFS(v, u);
			merge(u, v);
		}
	}
	ans[u] = st[FindPar(u)].size();
}
void Solve(int t)
{
	cin >> n;
	MakeSet(n);
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		st[i].insert(c[i]);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	DFS(1, 0);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " \n"[i == n];
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

