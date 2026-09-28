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
#define MOD         998244353
#define dbg(x)      cerr << #x << " = " << x << '\n'
#define UNIQUE(X)   (X).erase(unique(all(X)),(X).end())
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using orderset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/**
 * dp[i] = # of pairs (a,b) from c[i,...., n-1]
 * dp[i] = f(c[i])*dp[i+1] + (c[i]==1)*f(10*c[i]+c[i+1])*dp[i+2]
 * base case: dp[n] = 1, dp[n+1] = 0
 * answer will be dp[0]
 * M * [dp[i+1], dp[i+2]] = [dp[i], dp[i+1]]
 * M = [{f(c[i], (c[i]==1)*f(10*c[i]+c[i+1]))}, {1, 0}]
 *
 * [{dp[0]}, {dp[1]}] = M0 * M1 * ... * M(n-1) * [{dp[n], dp[n+1]}]
 * M = M0 * M1 * ... * M(n-1)
 * final result will be M.a[0][0]

**/

const int N = 5e5 + 5;

struct Mat {
    int n, m;
    int a[2][2];
    Mat() { }
    Mat(int _n, int _m) {
        n = _n; m = _m;
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
    }
    inline Mat operator * (const Mat &b) {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + 1LL * a[i][k] * b.a[k][j] % MOD) % MOD;
                }
            }
        }
        return ans;
    }
};

struct segtree
{
#define lft (node<<1)
#define rgt ((node<<1)|1)

    std::vector<Mat> tree;
    segtree() {}
    segtree(int n) {
        Mat m(2, 2);
        m.a[0][0] = 1;
        m.a[0][1] = 0;
        m.a[1][0] = 0;
        m.a[1][1] = 1;
        tree.assign(4 * n, m);
    }

    inline Mat merge(Mat a, Mat b) {
        return a * b;
    }

    void Update(int node, int b, int e, int i, Mat val) {
        if (i < b || i > e) return ;
        if (b == e && b == i) {
            tree[node] = val;
            return ;
        }
        int mid = (b + e) >> 1;
        Update(lft, b, mid, i, val);
        Update(rgt, mid + 1, e, i, val);
        tree[node] = merge(tree[lft], tree[rgt]);
    }

    Mat Query(int node, int b, int e, int i, int j) {
        Mat m(2, 2);
        m.a[0][0] = 1;
        m.a[0][1] = 0;
        m.a[1][0] = 0;
        m.a[1][1] = 1;
        if (j < b || i > e) return m;
        if (b >= i && e <= j) {
            return tree[node];
        }
        int mid = (b + e) >> 1;
        return merge(Query(lft, b, mid, i, j), Query(rgt, mid + 1, e, i, j));
    }
};

ll n, q;
string s;
vector<int> v;
int f(int d)
{
    if (d <= 9) return d + 1;
    return 19 - d;
}
void printMatrix(Mat m) {
    cout << m.a[0][0] << " " << m.a[0][1] << nl;
    cout << m.a[1][0] << " " << m.a[1][1] << nl;
    cout << nl;
}
void Solve()
{
    cin >> n >> q;
    cin >> s;
    for (auto it : s) v.push_back(it - '0');

    segtree st(n);
    Mat m(2, 2);
    for (int i = 0; i < n; i++) {
        m.a[1][0] = 1; m.a[1][1] = 0;
        m.a[0][0] = f(v[i]);
        if (i + 1 < n)
            m.a[0][1] = (v[i] == 1) * f(10 * v[i] + v[i + 1]);
        st.Update(1, 0, n - 1, i, m);

        // printMatrix(m);

    }

    Mat res;
    while (q--)
    {
        int i, d;
        cin >> i >> d;
        i--;
        v[i] = d;

        m.a[1][0] = 1; m.a[1][1] = 0;
        m.a[0][0] = f(v[i]);
        if (i + 1 < n)
            m.a[0][1] = (v[i] == 1) * f(10 * v[i] + v[i + 1]);
        st.Update(1, 0, n - 1, i, m);
        if (i > 0)
        {
            m.a[1][0] = 1; m.a[1][1] = 0;
            m.a[0][0] = f(v[i - 1]);
            m.a[0][1] = (v[i - 1] == 1) * f(10 * v[i - 1] + v[i]);
            st.Update(1, 0, n - 1, i - 1, m);
        }

        res = st.Query(1, 0, n - 1, 0, n - 1);
        cout << res.a[0][0] << nl;

        // printMatrix(res);
    }
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

