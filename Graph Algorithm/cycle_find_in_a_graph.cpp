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

int n, k, indeg[N];
vector<int> graph[N];

int vis[N], recstack[N];
bool cycle = 0;


void DFS(int u) {
	vis[u] = 1;
	recstack[u] = 1;
	for (auto v : graph[u]) {
		if (recstack[v])
			cycle = 1;
		if (!vis[v])
			DFS(v);
	}
	recstack[u] = 0;
}
void Solve()
{
	cin >> n >> k;
	for (int i = 1; i <= k; i++) {
		int u, v; cin >> u >> v;
		graph[v].push_back(u);
		indeg[u]++;
	}
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (indeg[i] == 0)
			q.push(i);
	}
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (auto v : graph[u]) {
			indeg[v]--;
			if (indeg[v] == 0)
				q.push(v);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (indeg[i])
			cycle = 1;
	}
	cout << (cycle ? "Yes there is a cycle\n" : "there is not a cylce\n");


	// Alternative solution: DFS
	cycle = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i])
			DFS(i);
	}

	for (int i = 1; i <= n; i++) {
		graph[i].clear();
		indeg[i]  = 0;
		vis[i] = 0;
		recstack[i] = 0;
		cycle = 0;
	}
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
