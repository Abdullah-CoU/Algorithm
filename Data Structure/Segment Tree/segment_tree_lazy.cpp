#include<bits/stdc++.h>
#define ll                  long long
#define endl                '\n'
#define F                   first
#define S                   second
#define all(a)              (a.begin()),(a.end())
#define UNIQUE(X)           (X).erase(unique(all(X)),(X).end())
#define SORT_UNIQUE(c)      (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define ms(a,b)             memset(a, b, sizeof(a))
#define Input               freopen("in.txt","r",stdin)
#define Output              freopen("out.txt","w",stdout)
#define MOD                 1000000007
using namespace std;

const int N = 200005;


int a[N];


struct segtree
{
#define lft (node<<1)
#define rgt ((node<<1)|1)

    vector<ll> tree, lazy;
    segtree() {}
    segtree(int n) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    inline void push(int node, int b, int e) {
        if (tree[node] == 0) return ;
        tree[node] = tree[node] + (e - b + 1) * lazy[node];
        if (b != e)
        {
            lazy[lft] = lazy[lft] + lazy[node];
            lazy[rgt] = lazy[rgt] + lazy[node];
        }
        lazy[node] = 0;
    }

    inline ll merge(ll a, ll b) {
        return a + b;
    }

    void Build(int node, int b, int e) {
        lazy[node] = 0;
        if (b == e) {
            tree[node] = a[b];
            return ;
        }
        int mid = (b + e) >> 1;
        Build(lft, b, mid);
        Build(rgt, mid + 1, e);
        tree[node] = merge(tree[lft], tree[rgt]);
    }

    void Update(int node, int b, int e, int i, ll val) {
        push(node, b, e);
        if (i < b || i > e) return ;
        if (b == e && b == i) {
            lazy[node] = val;// set lazy
            push(node, b, e);
            return ;
        }
        int mid = (b + e) >> 1;
        Update(lft, b, mid, i, val);
        Update(rgt, mid + 1, e, i, val);
        tree[node] = merge(tree[lft], tree[rgt]);
    }

    ll Query(int node, int b, int e, int i, int j) {
        push(node, b, e);
        if (j < b || i > e) return 0;
        if (b >= i && e <= j) {
            return tree[node];
        }
        int mid = (b + e) >> 1;
        return merge(Query(lft, b, mid, i, j), Query(rgt, mid + 1, e, i, j));
    }

};


void Solve(int t)
{
    ;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, T = 1;
    // cin >> T;
    for (t = 1; t <= T; t++)
        Solve(t);
    return 0;
}


