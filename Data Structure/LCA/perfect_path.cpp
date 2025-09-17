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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll my_rand(ll l, ll r)
{
	return uniform_int_distribution<ll>(l , r) (rng);
}

const int N = 2e5 + 5;

int parent[20][N], level[N];
std::vector<int> graph[N];

void DFS_LCA(int u, int par = 0)
{
	parent[0][u] = par;
	for (int i = 1; i <= 19; i++) {
		parent[i][u] = parent[i - 1][parent[i - 1][u]];
	}
	for (auto v : graph[u])
	{
		if (v != par) {
			level[v] = level[u] + 1;
			DFS_LCA(v, u);
		}
	}
}
int find_LCA(int x, int y) {
	if (level[x] < level[y]) swap(x, y);
	int diff = level[x] - level[y];
	// lift x up by diff
	for (int b = 0; b < 20; ++b) {
		if ((diff >> b) & 1) x = parent[b][x];
	}
	if (x == y) return x;
	for (int b = 19; b >= 0; --b) {
		int px = parent[b][x];
		int py = parent[b][y];
		if (px != py) {
			x = px;
			y = py;
		}
	}
	return parent[0][x];
}

int n, a[N], spf[N], v[N];
vector<int> primes, Rval;
map<int, int> serial;

void sieve()
{
	for (int i = 1; i < N; i++) spf[i] = i;
	for (int i = 2; i < N; i += 2) spf[i] = 2;
	for (int i = 3; i < N; i += 2)
	{
		for (int j = 2 * i; j < N; j += i) {
			spf[j] = min(spf[j], i);
		}
	}
	for (int i = 2; i < N; i++) {
		if (spf[i] == i) {
			serial[i] = primes.size();
			primes.push_back(i);
			Rval.push_back(my_rand(1, MOD - 1));
		}
	}
}
map<int, int> Factor;
void getFactor(int n)
{
	while (n > 1) {
		Factor[spf[n]]++;
		n /= spf[n];
	}
}

int pre[N], neg[N], preNeg[N], zero[N], preZero[N];

void DFS(int u, int par = 0)
{
	pre[u] = pre[par] ^ v[u];
	preNeg[u] = preNeg[par] ^ neg[u];
	preZero[u] = preZero[par] + zero[u];
	for (auto v : graph[u])
	{
		if (v != par) {
			DFS(v, u);
		}
	}
}
void Solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] == 0) {
			zero[i] = 1;
		}
		if (a[i] < 0) {
			neg[i]++;
		}
		a[i] = abs(a[i]);
		Factor.clear();
		getFactor(a[i]);
		for (auto it : Factor) {
			if (it.S % 2) {
				v[i] ^= Rval[serial[it.F]];
			}
		}
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	DFS_LCA(1);
	DFS(1);


	int q; cin >> q;
	while (q--) {
		int x, y; cin >> x >> y;
		int lca = find_LCA(x, y);
		int val = pre[x] ^ pre[y] ^ v[lca];
		int negval = preNeg[x] ^ preNeg[y] ^ neg[lca];
		int zerocnt = preZero[x] + preZero[y] - 2 * preZero[lca] + zero[lca];
		int fg = 0;
		if (zerocnt > 0)
			fg = 1;
		else if (negval % 2 == 0 and val == 0)
			fg = 1;
		cout << (fg ? "Yes\n" : "No\n");
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	sieve();
	int t, T = 1;
	// cin >> T;
	for (t = 1; t <= T; t++)
		Solve();
	return 0;
}
