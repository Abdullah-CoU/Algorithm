/**
 * find the bridges of the graph
 * Find the BCC
 * or Find the Bridge Tree
 * Find the path from 1 to n in the bridge tree
 * And Finally finds the suitable bridges in the path of 1 to n
 * Now, run a Multi Source BFS from all the suitable bridges
 * And calculate nearest Bridge for all cities
 * Print the answer for each queries
 **/


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

int n, m, vis[N], comp[N], low[N], disc[N], timer = 1, sz[N];
std::vector<pair<int, int>> graph[N], g[N], rg[N];

vector<int> bridges;
map<int, int> isBridge;

void DFS(int u, int id)
{
	low[u] = timer;
	disc[u] = timer;
	timer++;
	for (auto it : graph[u])
	{
		int v = it.F;
		int cId = it.S;
		if (cId == id)
			continue;
		if (!disc[v])
		{
			DFS(v, cId);
			low[u] = min(low[u], low[v]);
			if (low[v] > disc[u])
			{
				bridges.push_back(cId);
				isBridge[cId] = 1;
			}
		}
		else
		{
			low[u] = min(low[u], low[v]);
		}
	}
}


void DFS2(int u, int c) {
	comp[u] = c;
	vis[u] = 1;
	for (auto it : graph[u]) {
		int v = it.F;
		int id = it.S;
		if (isBridge[id]) continue;
		if (!vis[v]) {
			DFS2(v, c);
		}
	}
}
pair<int, int>  Prev[N];

void DFS3(int u, int p)
{
	Prev[u].F = p;
	for (auto it : g[u])
	{
		int v = it.F;
		int id = it.S;
		if (v == p)continue;
		Prev[v].S = id;
		DFS3(v, u);
	}
}

void Solve()
{
	vector<pair<int, int>> edges;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		graph[i].clear();
		g[i].clear();
		vis[i] = 0;
		disc[i] = 0;
		low[i] = 0;
	}
	bridges.clear();
	isBridge.clear();
	timer = 1;
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
		edges.push_back({u, v});
	}

	for (int i = 1; i <= n; i++) {
		if (!disc[i])
			DFS(i, 0);
	}


	for (int i = 1; i <= n; i++) vis[i] = 0 ;

	int c = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			DFS2(i, ++c);
		}
	}
	for (int i = 0; i < m; i++)
	{
		int u = edges[i].F, v = edges[i].S;
		if (comp[u] != comp[v]) {
			g[comp[u]].push_back({comp[v], i + 1});
			g[comp[v]].push_back({comp[u], i + 1});
		}
	}
	DFS3(comp[1], -1);

	vector<int> suitablebridges;
	int cur = comp[n];

	while (Prev[cur].F != -1) {
		suitablebridges.push_back(Prev[cur].S);
		cur = Prev[cur].F;
	}

	vector<int> res(n + 1, -1);
	for (int i = 1; i <= n; i++) vis[i] = 0;

	sort(all(suitablebridges));
	queue<pair<int, int>> q;
	for (auto it : suitablebridges) {

		q.push({it, edges[it - 1].F});
		q.push({it, edges[it - 1].S});
		vis[edges[it - 1].F] = 1;
		vis[edges[it - 1].S] = 1;
	}

	while (!q.empty())
	{
		int u = q.front().S;
		int id = q.front().F;
		q.pop();
		if (res[u] == -1)
			res[u] =  id;
		for (auto it : graph[u])
		{
			int v = it.F;
			if (!vis[v]) {
				q.push({id, v});
				vis[v] = 1;
			}
		}
	}

	int query; cin >> query;
	while (query--) {
		int c; cin >> c;
		cout << res[c] << " ";
	}
	cout << nl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, T = 1;
	cin >> T;
	for (t = 1; t <= T; t++)
		Solve();
	return 0;
}
