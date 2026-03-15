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

int vis[N], vis2[N], kingdom[N];
stack<int> st;

void DFS(int u) {
    vis[u] = 1;
    for (auto v : graph[u]) {
        if (!vis[v]) {
            DFS(v);
        }
    }
    st.push(u);
}

vector<int> comp;
void DFS2(int u, int st) {
    comp.push_back(u);
    vis2[u] = 1;
    kingdom[u] = st;
    for (auto v : rev_graph[u]) {
        if (!vis2[v]) {
            DFS2(v, st);
        }
    }
}
void Solve()
{
    int n , m;
    cin >> n >> m;
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
    while (!st.empty()) {
        if (!vis2[st.top()]) {
            nofscc++;
            comp.clear();
            DFS2(st.top(), nofscc);
            // for (auto it : comp) {
            //     cout << it << ' ';
            // }
            // cout << nl;
        }
        st.pop();
    }
    cout << nofscc << nl;
    for (int i = 1; i <= n; i++) {
        cout << kingdom[i] << " \n"[i == n];
    }
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
