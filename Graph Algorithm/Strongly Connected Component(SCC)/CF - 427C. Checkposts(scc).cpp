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

std::vector<int> graph[N], rev_graph[N];

int vis[N], end_time[N], timer = 1, vis2[N];
stack<int> st;

void DFS(int u) {
    vis[u] = 1;
    timer++;
    for (auto v : graph[u]) {
        if (!vis[v]) {
            DFS(v);
        }
    }
    end_time[u] = timer;
    st.push(u);
}

vector<int> comp;
ll a[N];
void DFS2(int u) {
    comp.push_back(a[u]);
    vis2[u] = 1;
    for (auto v : rev_graph[u]) {
        if (!vis2[v]) {
            DFS2(v);
        }
    }
}

void Solve()
{
    int n , m;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            DFS(i);
        }
    }
    int nofscc = 0;
    ll ans = 0, ways = 1;
    while (!st.empty()) {
        if (!vis2[st.top()]) {
            nofscc++;
            comp.clear();
            DFS2(st.top());
            sort(all(comp));
            ans += comp.front();
            ll c = 0;
            for (auto it : comp) {
                if (it == comp.front()) {
                    c++;
                }
            }
            ways = (ways * c) % MOD;
            // for (auto it : comp) {
            //     cout << it << ' ';
            // }
            // cout << nl;
        }
        st.pop();
    }
    // cout << nofscc << nl;
    cout << ans << ' ' << ways << nl;
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
