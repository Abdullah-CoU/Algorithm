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


const int N = 2e5 + 5;

int n, m, vis[N], comp[N];
std::vector<int> graph[N], rgraph[N], g[N];

stack<int> st;
void DFS1(int u)
{
    vis[u] = 1;
    for (auto v : graph[u]) {
        if (!vis[v]) {
            DFS1(v);
        }
    }
    st.push(u);
}
void DFS2(int u, int cur)
{
    vis[u] = 1;
    comp[u] = cur;
    for (auto v : rgraph[u]) {
        if (!vis[v]) {
            DFS2(v, cur);
        }
    }
}
ll sum[N], a[N], sub[N], dp[N];

void DFS(int u) {
    vis[u] = 1;
    sub[u] = sum[u];
    ll mx = 0;
    for (auto v : graph[u]) {
        if (!vis[v]) {
            DFS(v);
        }
        mx = max(mx, sub[v]);
    }
    sub[u] += mx;
}

void Solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> e;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        e.push_back({u, v});
        graph[u].push_back(v);
        rgraph[v].push_back(u);
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
    for (int i = 1; i <= n; i++) {
        sum[comp[i]] += a[i];
    }
    vector<int> indeg(n + 1, 0);
    for (auto it : e) {
        if (comp[it.F] != comp[it.S]) {
            g[comp[it.F]].push_back(comp[it.S]);
            indeg[comp[it.S]]++;
        }
    }
    memset(vis, 0, sizeof vis);
    queue<int> q;
    for (int i = 1; i <= scc; i++) {
        dp[i] = sum[i];
        if (indeg[i] == 0)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (auto v : g[u]) {
            dp[v] = max(dp[v], dp[u] + sum[v]);
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    // for (int i = 1; i <= scc; i++) if (!vis[i])
    //         DFS(i);
    ll ans = 0;
    for (int i = 1; i <= scc; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << nl;
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
