//https://codeforces.com/problemset/problem/238/C
//https://www.youtube.com/watch?v=2AeKqC05ucY

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
std::vector<pair<int, int>> edge[N];

int dp[N], mx1[N], mx2[N];

void dfs1(int u, int par = -1)
{
	for (auto &[v, w] : edge[u]) {
		if (v == par) continue;

		dp[1] += w;
		dfs1(v, u);
	}
}

void dfs2(int u, int par = -1)
{
	for (auto &[v, w] : edge[u]) {
		if (v == par) continue;

		dp[v] = dp[u] + (!w ? 1 : -1);
		dfs2(v, u);
	}
}
void dfs3(int u, int par = -1)
{
	mx1[u] = 0;
	mx2[u] = 0;
	for (auto &[v, w] : edge[u]) {
		if (v == par) continue;

		dfs3(v, u);

		int val = mx1[v] + (w ? 1 : -1);

		mx2[u] = max(mx2[u], val);
		if (mx2[u] > mx1[u]) swap(mx1[u], mx2[u]);
	}
}
void Solve()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back({v, 0});
		edge[v].push_back({u, 1});
	}
	dfs1(1);
	dfs2(1);

	int ans = n;
	for (int c = 1; c <= n; c++)
	{
		dfs3(c);
		ans = min(ans, dp[c] - mx1[c] - mx2[c]);
	}

	cout << ans << endl;
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
