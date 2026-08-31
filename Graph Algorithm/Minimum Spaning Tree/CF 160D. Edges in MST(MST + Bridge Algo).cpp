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
#define UNIQUE(X)   (X).erase(unique(all(X)),(X).end())
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using orderset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;



const int N = 2e5 + 5;

struct DSU {
    vector<int> par, rnk, sz;
    int c, mx = 1;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    int find(int i) {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return -1;
        else --c;
        par[i] = j;
        return j;
    }
};
vector<pii> graph[N], tmpGraph[N];
int low[N], disc[N], timer = 1, vis[N], res[N];

void DFS(int u, int edgeid)
{
    vis[u] = 1;
    low[u] = timer;
    disc[u] = timer;
    timer++;
    for (auto [v, id] : graph[u])
    {
        if (id == edgeid)
            continue;
        if (!disc[v])
        {
            DFS(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
            {
                res[id] = 1;
            }
        }
        else
        {
            low[u] = min(low[u], low[v]);
        }
    }
}

void Solve()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 4>> edges;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v, i});
    }
    sort(all(edges));
    DSU dsu(n);


    for (int i = 0; i < m; i++)
    {
        int j = i;
        while (j < m and edges[i][0] == edges[j][0])j++;
        for (int k = i; k < j; k++) {
            int u = edges[k][1];
            int v = edges[k][2];
            int w = edges[k][0];
            int id = edges[k][3];
            u = dsu.find(u);
            v = dsu.find(v);
            if (u == v) {
                res[id] = -1;
            }
            else {
                res[id] = 0;
                graph[u].push_back({v, id});
                graph[v].push_back({u, id});
            }
        }
        timer = 1;
        for (int k = i; k < j; k++) {
            int u = edges[k][1];
            int par = dsu.find(u);
            if (!vis[par]) DFS(par, 0);
        }
        for (int k = i; k < j; k++) {
            int u = edges[k][1];
            int v = edges[k][2];
            int w = edges[k][0];
            int id = edges[k][3];
            int parU = dsu.find(u);
            int parV = dsu.find(v);
            graph[parU].clear();
            graph[parV].clear();
            vis[parU] = vis[parV] = 0;
            disc[parU] = disc[parV] = 0;
            low[parU] = low[parV] = 0;
            if (parU != parV)
                dsu.par[parU] = parV;
        }
        i = j - 1;
    }

    for (int i = 1; i <= m; i++) {
        if (res[i] == -1)
            cout << "none\n";
        else if (res[i] == 1)
            cout << "any\n";
        else
            cout << "at least one\n";
        // cout << res[i] << " \n"[i == m];
    }
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
 
