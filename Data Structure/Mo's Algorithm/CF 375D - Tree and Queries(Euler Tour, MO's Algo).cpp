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
    int index, l, r, val;
    bool operator < (const Query &other)const {
        int Block_own = l / k;
        int Block_other = other.l / k;
        if (Block_other == Block_own)
            return r < other.r;
        return Block_own < Block_other;
    }
} query[N];
int fre[N], cnt[N];



void Add(int i)
{
    fre[c[order[i]]]++;
    cnt[fre[c[order[i]]]]++;
}
void Remove(int i)
{
    cnt[fre[c[order[i]]]]--;
    fre[c[order[i]]]--;
}
void Solve()
{
    order.push_back(0);
    int q;
    cin >> n >> q;
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

    for (int i = 1; i <= q; i++)
    {
        int v, x; cin >> v >> x;
        query[i].l = in[v];
        query[i].r = out[v];
        query[i].val = x;
        query[i].index = i;
    }
    sort(query + 1, query + q + 1);
    int l = 1, r = 0;
    vector<ll> ans(q + 5);
    for (int i = 1; i <= q; i++)
    {
        while (r < query[i].r) Add(++r);
        while (l < query[i].l) Remove(l++);
        while (r > query[i].r) Remove(r--);
        while (l > query[i].l) Add(--l);
        ans[query[i].index] = cnt[query[i].val];
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << " \n"[i == q];

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

