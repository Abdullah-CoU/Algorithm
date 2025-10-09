//https://codeforces.com/problemset/problem/219/D
//https://www.youtube.com/watch?v=YjpCgxOpsMg

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
int dp[N];

void dfs1(int u, int par = -1)
{
	for (auto &[v, w] : edge[u]) {
		if (v == par)continue;
		dp[1] += w;
		dfs1(v, u);
	}
}
void dfs2(int u, int par = -1) {
	for (auto &[v, w] : edge[u]) {
		if (v == par) continue;
		dp[v] = dp[u] + (!w ? 1 : -1);
		dfs2(v, u);
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
	vector<pair<int, int>> vec;
	for (int i = 1; i <= n; i++) {
		// cout << dp[i] << " \n"[i == n];
		vec.push_back({dp[i], i});
	}
	sort(all(vec));
	cout << vec[0].F << nl;
	for (int i = 0; i < n; i++) {
		if (vec[i].F == vec[0].F)
			cout << vec[i].S << ' ';
	}
	cout << nl;
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
