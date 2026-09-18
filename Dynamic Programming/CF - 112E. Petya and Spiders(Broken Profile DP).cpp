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



const int N = 2e5 + 5;


int n, m, dp[40][6][64][64][64];

int FuN(int i, int j, int pmask, int mask, int nmask)
{
    if (i >= n) {
        if (pmask == (1 << m) - 1)
            return 0;
        return 1e9;
    }
    if (j >= m) {
        if (pmask == (1 << m) - 1)
            return FuN(i + 1, 0, mask, nmask, 0);
        return 1e9;
    }
    if (dp[i][j][pmask][mask][nmask] != -1)
        return dp[i][j][pmask][mask][nmask];

    int ret = 1e9;

    int x = mask | (1 << j);
    if (j > 0)x = x | (1 << (j - 1));
    if (j + 1 < m)x = x | (1 << (j + 1));

    ret = min(ret, 1 + FuN(i, j + 1, pmask | (1 << j), x, nmask | (1 << j)));
    ret = min(ret, FuN(i, j + 1, pmask, mask, nmask));

    return dp[i][j][pmask][mask][nmask] = ret;
}

void Solve()
{
    cin >> n >> m;
    if (n < m)swap(n, m);
    memset(dp, -1, sizeof dp);
    cout << n*m - FuN(0, 0, (1 << m) - 1, 0, 0) << nl;
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


