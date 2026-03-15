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
std::vector<int> graph[N], rgraph[N];

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
int x = 0, y = 0, fg = 1;
void DFS(int u)
{
    vis[u] = 1;
    for (auto v : graph[u])
    {
        if (!vis[v]) {
            DFS(v);
        }
        if (comp[u] != comp[v]) {
            x = v, y = u;
        }
    }
}
void Solve()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
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
    if (scc == 1) {
        cout << "YES\n";
        return ;
    }
    cout << "NO\n";
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            DFS(i);
        }
    }
    if (x == 0 or y == 0) {
        x = 1;
        for (int i = 2; i <= n; i++) {
            if (comp[i] != comp[x])
                y  = i;
        }
    }
    cout << x << ' ' << y << nl;
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
