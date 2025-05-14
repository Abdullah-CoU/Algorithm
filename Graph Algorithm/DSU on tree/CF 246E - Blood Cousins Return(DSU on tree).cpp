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

/**     Order Set       **/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using orderset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


const int N = 1e5 + 5;

int n, sz[N], cnt[N], level[N], res[N];
std::vector<int> graph[N], vec[N];
vector<pair<int, int>> query[N];
string s[N];
map<string, int> m[N];
// orderset<pair<int, string>> os[N];
// map<string, int> m;

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
	m[level[v]][s[v]]++;
	for (auto u : graph[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				vec[v].push_back(x);
				m[level[x]][s[x]]++;
			}
		}
	}
	for (auto [l, id] : query[v]) {
		res[id] = m[level[v] + l].size();
	}
	if (keep == 0) {
		for (auto u : vec[v]) {
			m[level[u]][s[u]]--;
			if (m[level[u]][s[u]] == 0) {
				m[level[u]].erase(s[u]);
			}
		}
	}

}
void Solve(int t)
{
	cin >> n;

	vector<int> root;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
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
		if (level[v] + p <= n)
			query[v].push_back({p, i});
	}

	for (auto v : root) {
		DFS(v);
	}
	for (int i = 1; i <= q; i++) {
		cout << res[i] << "\n";
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

