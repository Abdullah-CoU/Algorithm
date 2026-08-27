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

#define uint unsigned int

const int N = 2e5 + 5;


struct Mat {
    int n, m;
    vector<vector<uint>> a;
    Mat() { }
    Mat(int _n, int _m) {n = _n; m = _m; a.assign(n, vector<uint>(m, 0)); }
    Mat(vector< vector<uint> > v) { n = v.size(); m = n ? v[0].size() : 0; a = v; }
    inline void make_unit() {
        assert(n == m);
        for (int i = 0; i < n; i++)  {
            for (int j = 0; j < n; j++) a[i][j] = i == j;
        }
    }
    inline Mat operator + (const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans.a[i][j] = (a[i][j] + b.a[i][j]);
            }
        }
        return ans;
    }
    inline Mat operator - (const Mat &b) {
        assert(n == b.n && m == b.m);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans.a[i][j] = (a[i][j] - b.a[i][j]);
            }
        }
        return ans;
    }
    inline Mat operator * (const Mat &b) {
        assert(m == b.n);
        Mat ans = Mat(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.a[i][j] = (ans.a[i][j] + a[i][k] * b.a[k][j]);
                }
            }
        }
        return ans;
    }
    inline Mat pow(long long k) {
        assert(n == m);
        Mat ans(n, n), t = a; ans.make_unit();
        while (k) {
            if (k & 1) ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }
    inline Mat& operator += (const Mat& b) { return *this = (*this) + b; }
    inline Mat& operator -= (const Mat& b) { return *this = (*this) - b; }
    inline Mat& operator *= (const Mat& b) { return *this = (*this) * b; }
    inline bool operator == (const Mat& b) { return a == b.a; }
    inline bool operator != (const Mat& b) { return a != b.a; }
};

unsigned int C[55][55];

void Solve()
{
    ll n, k;
    cin >> n >> k;
    Mat init(k + 2, 1);
    for (int i = 0; i < k + 2; i++)
        init.a[i][0] = 1;

    Mat m(k + 2, k + 2);
    m.a[0][0] = 1;
    for (int i = 1; i <= k + 1; i++)
        m.a[0][i] = C[k][k - i + 1];
    for (int i = 1; i <= k + 1; i++)
    {
        int x = k - i + 1, y = 0;
        for (int j = k + 1; ; j--) {
            if (y > x) break;
            m.a[i][j] = C[x][y];
            y++;
        }
    }

    m = m.pow(n - 1);
    m = m * init;

    cout << m.a[0][0] << nl;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, T = 1;
    for (int i = 0; i <= 50; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    cin >> T;
    for (t = 1; t <= T; t++) {
        cout << "Case " << t << ": ";
        Solve();
    }
    return 0;
}

