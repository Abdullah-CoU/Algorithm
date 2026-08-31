/**
 * CF 888G. Xor-MST
 * Boruvka's Algorithm
 * iterate until # of component > 1
 * find the minimum edge from each component
 * minimum edge in this problem is minimum xor value
 * we use trie to find minimum xor value and its index
 * then connect the edge in the dsu without creating cycles
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

struct Edge {
    int u, v, w;
};
bool comp(Edge a, Edge b) {
    return a.w < b.w;
}
int to[N * 30][2], tot_nodes = 1;
int el[N * 30], cnt[N * 30];

void Add(int x, int id) {
    int cur = 1;
    cnt[cur]++;
    for (int i = 30; i >= 0; i--) {
        bool b = x & (1 << i);
        if (to[cur][b] == 0) to[cur][b] = ++tot_nodes;
        cur = to[cur][b];
        cnt[cur]++;
    }
    el[cur] = id;
}

void Del(int x, int id) {
    int cur = 1;
    cnt[cur]--;
    for (int i = 30; i >= 0; i--) {
        bool b = x & (1 << i);
        cur = to[cur][b];
        cnt[cur]--;
    }
    el[cur] = 0;
}

int minxor(int x) {
    int cur = 1;
    for (int i = 30; i >= 0; i--) {
        bool b = x & (1 << i);
        if (to[cur][b] && cnt[to[cur][b]] > 0)
            cur = to[cur][b];
        else
            cur = to[cur][!b];
    }
    return el[cur];
}
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
int n, m, a[N];
vector<int> vec[N];

void Solve()
{
    cin >> n;
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }

    sort(all(v));
    UNIQUE(v);
    n = 0;
    for (auto it : v)
        a[++n] = it;
    DSU d(n);
    ll ans = 0;

    while (d.count() > 1)
    {
        for (int i = 1; i <= n; i++) {
            vec[d.find(i)].push_back(i);
            Add(a[i], i);
        }
        vector<Edge> edges;
        for (int i = 1; i <= n; i++) {
            if (vec[i].empty()) continue;
            for (auto it : vec[i])
                Del(a[it], it);
            pii nw = {2e9, 2e9};
            for (auto it : vec[i]) {
                int k = minxor(a[it]);
                nw = min(nw, {a[it]^a[k], k});
            }
            edges.push_back({i, nw.S, nw.F});
            for (auto it : vec[i])
                Add(a[it], it);
        }
        sort(edges.begin(), edges.end(), comp);
        for (int i = 0; i < edges.size(); i++) {
            if (d.find(edges[i].u) != d.find(edges[i].v)) {
                ans += edges[i].w;
                d.merge(edges[i].u, edges[i].v);
            }
        }

        for (int i = 1; i <= n; i++) {
            vec[i].clear();
        }
        for (int i = 0; i <= tot_nodes; i++) {
            to[i][0] = to[i][1] = 0;
            cnt[i] = 0;
        }
        tot_nodes = 1;

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

