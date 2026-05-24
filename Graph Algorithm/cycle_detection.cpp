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
#define int128      __int128
#define gcd         __gcd
#define pii         pair<int,int>
#define MOD         1000000007
#define dbg(x)      cerr << #x << " = " << x << '\n'
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using orderset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;



const int N = 2e5 + 5;

int n, m, vis[N], par[N];
vector<int> graph[N];
vector<int> cycle;

bool dfs(int u, int parent)
{
    if (!cycle.empty())return 1;

    vis[u] = 1;

    for (auto v : graph[u]) {
        if (v == parent) continue;

        if (!vis[v]) {
            par[v] = u;
            if (dfs(v, u)) return 1;
        }
        else if (vis[v] == 1) {
            // cycle found
            cycle.push_back(v);
            for (int x = u; x != v; x = par[x]) {
                cycle.push_back(x);
            }
            cycle.push_back(v);
            return 1;
        }
    }
    return 0;
}
void Solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i] and dfs(i, -1)) {
            cout << cycle.size() << nl;
            for (auto it : cycle) cout << it << " ";
            cout << nl;
            return ;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, T = 1;
    // cin >> T;
    for (t = 1; t <= T; t++)
        Solve();
    return 0;
}

// https://cses.fi/problemset/task/1669/
