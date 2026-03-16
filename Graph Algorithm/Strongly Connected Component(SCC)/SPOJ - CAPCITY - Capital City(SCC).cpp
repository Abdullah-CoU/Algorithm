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
void Solve()
{
    cin >> n >> m;

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
    // cout << scc << nl;
    vector<int> outdeg(n + 1, 0);
    for (auto it : e) {
        if (comp[it.F] != comp[it.S]) {
            g[comp[it.F]].push_back(comp[it.S]);
            outdeg[comp[it.F]]++;
        }
    }
    int cnt = 0, id = 0;;
    for (int i = 1; i <= scc; i++) {
        if (outdeg[i] == 0) {
            cnt++;
            id = i;
        }
    }
    vector<int> res;
    if (cnt == 1) {
        for (int i = 1; i <= n; i++) {
            if (comp[i] == id)
                res.push_back(i);
        }
    }
    cout << res.size() << nl;
    for (auto it : res)
        cout << it << ' ';
    cout << nl;
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
