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


const int N = 5e5 + 5;

int n, m, col[N], sz[N], cnt[26][N], level[N], res[N];
std::vector<int> graph[N], vec[N];
vector<pair<int, int>> query[N];
string s;

void DFS_size(int v, int p) {
	sz[v] = 1;
	level[v] = level[p] + 1;
	for (auto u : graph[v]) {
		if (u != p) {
			DFS_size(u, v);
			sz[v] += sz[u];
		}
	}
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

	cnt[s[v - 1] - 'a'][level[v]]++;
	for (auto u : graph[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				cnt[s[x - 1] - 'a'][level[x]]++;
				vec[v].push_back(x);
			}
		}
	}
	for (auto[l, id] : query[v]) {
		int odd = 0;
		for (int i = 0; i < 26; i++) {
			if (cnt[i][l] & 1) odd++;
		}
		if (odd <= 1)
			res[id] = 1;
		else
			res[id] = 0;
	}
	if (keep == 0) {
		for (auto u : vec[v]) {
			cnt[s[u - 1] - 'a'][level[u]]--;
		}
	}

}
void Solve(int t)
{
	int q;
	cin >> n >> q;
	for (int i = 2; i <= n; i++) {
		int p; cin >> p;
		graph[i].push_back(p);
		graph[p].push_back(i);
	}

	cin >> s;
	for (int i = 1; i <= q; i++) {
		int v, h;
		cin >> v >> h;
		query[v].push_back({h, i});
	}
	DFS_size(1, 0);
	DFS(1, 0, 0);
	for (int i = 1; i <= q; i++) {
		cout << (res[i] ? "Yes" : "No") << "\n";
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

