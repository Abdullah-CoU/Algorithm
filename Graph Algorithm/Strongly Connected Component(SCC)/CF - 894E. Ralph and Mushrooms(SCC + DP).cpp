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


const int N = 1e6 + 5;

int n, m, vis[N], comp[N];
std::vector<pair<int, int>> graph[N], rgraph[N], g[N];

stack<int> st;
void DFS1(int u)
{
    vis[u] = 1;
    for (auto it : graph[u]) {
        int v = it.F;
        if (!vis[v]) {
            DFS1(v);
        }
    }
    st.push(u);
}

// 4 3 1
ll value(ll x) {
    ll lo = 0, hi = 100000000, res;
    while (lo <= hi) {
        ll mid = (lo + hi) >> 1;
        if ((mid * (mid + 1)) / 2 <= x) {
            res = mid;
            lo = mid + 1;
        }
        else
            hi = mid - 1;
    }

    return (x * (res + 1)) - (res * (res + 1) * (res + 2)) / 6;

}

ll sum[N], dp[N];

void DFS2(int u, int cur)
{
    vis[u] = 1;
    comp[u] = cur;
    for (auto it : rgraph[u]) {
        int v = it.F;
        int w = it.S;
        if (!vis[v]) {
            DFS2(v, cur);
        }
    }
}
ll DFS(int u)
{
    if (dp[u] != -1) return dp[u];
    ll ans = sum[u];
    for (auto it : g[u])
    {
        int v = it.F;
        int w = it.S;
        ans = max(ans, sum[u] + w + DFS(v));
    }
    return dp[u] = ans;
}
void Solve()
{
    cin >> n >> m;

    vector<pair<pair<int, int>, int>> e;
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        e.push_back({{u, v}, w});
        graph[u].push_back({v, w});
        rgraph[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            DFS1(i);
    }
    memset(vis, 0, sizeof vis);
    int scc = 0;
    while (!st.empty()) {
        int src = st.top();
        st.pop();
        if (!vis[src]) {
            scc++;
            DFS2(src, scc);
        }
    }

    for (auto it : e) {
        if (comp[it.F.F] != comp[it.F.S]) {
            g[comp[it.F.F]].push_back({comp[it.F.S], it.S});
        } else {
            sum[comp[it.F.F]] += value(it.S);
        }
    }

    memset(vis, 0, sizeof vis);
    memset(dp, -1, sizeof dp);

    int start; cin >> start;
    ll ans = DFS(comp[start]);
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
