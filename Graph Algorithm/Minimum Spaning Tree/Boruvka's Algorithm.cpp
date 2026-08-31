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

struct Edge
{
    int u, v, w;
};
struct DSU {
    vector<int> par, rnk, sz;
    int c, mx = 1;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    int find(int i) {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j) {
        return find(i) == find(j);
    }
    int count() {
        return c;    //connected components
    }
    int merge(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return 0;
        else --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        mx = max(mx, sz[j]);
        if (rnk[i] == rnk[j]) rnk[j]++;
        return 1;
    }
};
int n, m, mnedge[N];

void Solve()
{
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    DSU d(n);
    ll ans = 0;

    while (d.count() > 1)
    {
        for (int i = 1; i <= n; i++) mnedge[i] = -1;
        for (int i = 0; i < m; i++)
        {
            if (d.same(edges[i].u, edges[i].v)) continue;
            int pU = d.find(edges[i].u);
            if (mnedge[pU] == -1 or edges[i].w < edges[mnedge[pU]].w) {
                mnedge[pU] = i;
            }
            int pV = d.find(edges[i].v);
            if (mnedge[pV] == -1 or edges[i].w < edges[mnedge[pV]].w) {
                mnedge[pV] = i;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (mnedge[i] != -1) {
                if (d.merge(edges[mnedge[i]].u, edges[mnedge[i]].v)) {
                    ans += edges[mnedge[i]].w;
                }
            }
        }
    }

    cout << ans << nl;
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

// SPOJ - MST
