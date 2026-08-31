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

int n, k, c[N], in[N], out[N], timer = 0;
vector<int> g[N];
vector<ll> order;
void dfs(int u, int p) {
    timer++;
    in[u] = timer;
    order.push_back(u);
    for (auto v : g[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    out[u] = timer;
}

struct Query {
    int index, l, r;
    bool operator < (const Query &other)const {
        int Block_own = l / k;
        int Block_other = other.l / k;
        if (Block_other == Block_own)
            return r < other.r;
        return Block_own < Block_other;
    }
} query[N];
ll sum[N];
int fre[N];
// multiset<int> ms;
// order[i]
int mxfreq = 0;
void Add(int i)
{
    sum[fre[c[order[i]]]] -= c[order[i]];
    fre[c[order[i]]]++;
    mxfreq = max(mxfreq, fre[c[order[i]]]);
    // ms.insert(fre[c[order[i]]]);
    sum[fre[c[order[i]]]] += c[order[i]];
}
void Remove(int i)
{
    sum[fre[c[order[i]]]] -= c[order[i]];
    // ms.erase(ms.lower_bound(fre[c[order[i]]]));
    fre[c[order[i]]]--;
    if (sum[mxfreq] == 0)
        mxfreq--;
    sum[fre[c[order[i]]]] += c[order[i]];
}
void Solve()
{
    order.push_back(0);
    cin >> n;
    k = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    // for (int i = 1; i <= n; i++) {
    //     cout << in[i] << " " << out[i] << nl;
    // }

    for (int i = 1; i <= n; i++)
    {
        query[i].l = in[i];
        query[i].r = out[i];
        query[i].index = i;
    }
    sort(query + 1, query + n + 1);
    int l = 1, r = 0;
    vector<ll> ans(n + 5);
    for (int i = 1; i <= n; i++)
    {
        while (r < query[i].r) Add(++r);
        while (l < query[i].l) Remove(l++);
        while (r > query[i].r) Remove(r--);
        while (l > query[i].l) Add(--l);
        ans[query[i].index] = sum[mxfreq];
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];

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

