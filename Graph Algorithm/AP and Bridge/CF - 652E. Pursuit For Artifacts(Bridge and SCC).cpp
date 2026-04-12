/**
 * find the bridges of the graph
 * create another graph with only the bridge(biconnected component graph)
 * new graph will be a tree
 * now find the path from a to b
 * check is there a artifact of the path
 * or a artifact inside a new componenent(node)
 * print the answer
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


const int N = 3e5 + 5;

int n, m, vis[N], comp[N], low[N], disc[N], timer = 1, artifact3[N];
std::vector<int> graph[N], g[N], rg[N];
map<pair<int, int>, int> artifact, bridges, artifact2;
// vector<pair<int, int>> bridge;


void DFS(int u, int par)
{
    low[u] = timer;
    disc[u] = timer;
    timer++;
    for (auto v : graph[u])
    {
        if (v == par)
            continue;
        if (!disc[v])
        {
            DFS(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u])
            {
                // bridge.push_back({u, v});
                bridges[ {u, v}] = 1;
                bridges[ {v, u}] = 1;
            }
        }
        else
        {
            low[u] = min(low[u], low[v]);
        }
    }
}

// void DFS1(int u) {
//     vis[u] = 1;
//     for (auto v : graph[u]) {
//         if (!vis[v]) {
//             g[u].push_back(v);
//             DFS1(v);
//         }
//     }
// }
void DFS2(int u, int c) {
    comp[u] = c;
    vis[u] = 1;
    for (auto v : graph[u]) {
        if (bridges[ {u, v}]) continue;
        if (!vis[v]) {
            DFS2(v, c);
        }
    }
}
int ans = 0, previous[N];
void DFS3(int u) {
    vis[u] = 1;
    for (auto v : g[u]) {
        if (!vis[v]) {
            previous[v] = u;
            DFS3(v);
        }
    }
}
void Solve()
{
    vector<pair<int, int>> edges;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
        if (w) {
            artifact[ {u, v}] = 1;
            artifact[ {v, u}] = 1;
        }
    }
    memset(vis, 0, sizeof vis);
    DFS(1, 0);
    memset(vis, 0, sizeof vis);
    int c = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            DFS2(i, ++c);
        }
    }
    for (int i = 0; i < m; i++) {
        int u = edges[i].F;
        int v = edges[i].S;
        if (comp[u] != comp[v]) {
            // cout << comp[u] << ' ' << comp[v] << nl;
            g[comp[u]].push_back(comp[v]);
            g[comp[v]].push_back(comp[u]);
            if (artifact[ {u, v}]) {
                artifact2[ {comp[u], comp[v]}] = 1;
                artifact2[ {comp[v], comp[u]}] = 1;
            }
        }
        else {
            if (artifact[ {u, v}])
                artifact3[comp[u]] = 1;
        }
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << comp[i] << " \n"[i == n];
    // }
    memset(vis, 0, sizeof vis);
    int a, b; cin >> a >> b;
    DFS3(comp[a]);

    int cur = comp[b];
    while (cur) {
        // cout << cur << nl;
        if (artifact3[cur]) ans = 1;
        if (artifact2[ {cur, previous[cur]}]) ans = 1;
        cur = previous[cur];
    }

    cout << (ans ? "YES" : "NO") << nl;
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
