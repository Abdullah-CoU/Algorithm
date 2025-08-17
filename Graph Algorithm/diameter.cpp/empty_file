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

int n, f[N], g[N], diameter = 0;
std::vector<int> graph[N];

void DFS(int u, int par)
{
	vector<int> fvalues;
	for (auto v : graph[u])
	{
		if (v == par) continue;
		DFS(v, u);
		fvalues.push_back(f[v]);
	}
	sort(all(fvalues));
	reverse(all(fvalues));

	f[u] = 1;

	if (!fvalues.empty()) f[u] = 1 + fvalues[0];

	if (fvalues.size() >= 2) g[u] = 1 + fvalues[0] + fvalues[1];

	diameter = max(diameter, max(f[u], g[u]));
}
void Solve()
{
	cin >> n;
	for (int i = 2; i <= n; i++) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);;
	}
	DFS(1, 0);
	cout << diameter - 1 << nl;
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
