/**
 * find the bridges of the graph
 * transform the graph into biconnected component graph
 * direct the edges of the non-bridges
 * create a cycle for each component
 * start a DFS from the largest component
 * direct the bridges from lower component to higher component
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


const int N = 4e5 + 5;

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
void DFS2(int u, int c, int &cnt) {
    comp[u] = c;
    vis[u] = 1;
    cnt++;
    for (auto v : graph[u]) {
        if (bridges[ {u, v}]) continue;
        if (!vis[v]) {
            DFS2(v, c, cnt);
        }
    }
}

map<pair<int, int>, int> direction, bridgeDirection;

void DFS3(int u)
{
    vis[u] = 1;
    for (auto v : graph[u])
    {
        if (bridges[ {u, v}]) continue;

        if (!vis[v]) {
            direction[ {u, v}] = 1;
            DFS3(v);
        }
        else {
            if (!direction[ {u, v}] and !direction[ {v, u}])
                direction[ {u, v}] = 1;
        }
    }
}
void DFS4(int u) {
    vis[u] = 1;
    for (auto v : g[u])
    {
        if (!vis[v]) {
            bridgeDirection[ {v, u}] = 1;
            DFS4(v);
        }
    }
}
void Solve()
{
    vector<pair<int, int>> edges;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
    }

    memset(vis, 0, sizeof vis);
    DFS(1, 0);

    memset(vis, 0, sizeof vis);
    int c = 0, mx = 0, start = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int cnt = 0;
            DFS2(i, ++c, cnt);
            if (cnt > mx) {
                mx = cnt;
                start = i;
            }
        }
    }

    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i]) {
            DFS3(i);
        }
    }

    for (auto it : edges)
    {
        int u = it.F;
        int v = it.S;

        if (comp[u] != comp[v]) {
            g[comp[u]].push_back(comp[v]);
            g[comp[v]].push_back(comp[u]);
        }
    }

    memset(vis, 0, sizeof vis);

    DFS4(comp[start]);

    cout << mx << nl;
    for (auto it : edges)
    {
        int u = it.F;
        int v = it.S;

        if (bridges[ {u, v}]) {
            if (bridgeDirection[ {comp[u], comp[v]}])
                ;
            else
                swap(u, v);
        }
        else {
            if (direction[ {u, v}])
                ;
            else
                swap(u, v);
        }
        cout << u << ' ' << v << nl;
    }
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
