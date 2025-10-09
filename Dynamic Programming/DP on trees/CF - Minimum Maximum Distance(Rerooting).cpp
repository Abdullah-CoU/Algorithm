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

int n, k, a[N], f[N], mx1[N], mx2[N];
std::vector<int> graph[N];

void DFS1(int u, int p)
{
    mx1[u] = -1e9;
    mx2[u] = -1e9;
    for (auto v : graph[u]) {
        if (v != p) {
            DFS1(v, u);
            if (mx1[v] + 1 > mx1[u]) {
                mx2[u] = mx1[u];
                mx1[u] = mx1[v] + 1;
            } else if (mx1[v] + 1 > mx2[u]) {
                mx2[u] = mx1[v] + 1;
            }
            // f[u] = max(f[u], 1 + f[v]);
        }
    }
    if (a[u]) {
        mx1[u] = max(0, mx1[u]);
    }
}
void DFS2(int u, int p, int cur)
{
    f[u] = max(mx1[u], cur);
    if (a[u])
        f[u] = max(f[u], 0);
    for (auto v : graph[u]) {
        if (v != p) {
            if (mx1[v] + 1 == mx1[u]) {
                int temp = max(cur, mx2[u]) + 1;
                if (a[u])
                    temp = max(temp, 1);
                DFS2(v, u, temp);
            }
            else
                DFS2(v, u, f[u] + 1);
        }
    }
}

void Solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        f[i] = -1e9;
        a[i] = 0;
        mx1[i] = mx2[i] = -1e9;
    }
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        a[x] = 1;
    }


    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    DFS1(1, 0);
    DFS2(1, 0, -1e9);
    int ans = 1e9;
    for (int i = 1; i <= n; i++) {
        // cout << f[i] << " \n"[i == n];
        ans = min(ans, f[i]);
    }
    cout << ans << nl;
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, T = 1;
    cin >> T;
    for (t = 1; t <= T; t++)
        Solve();
    return 0;
}
