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


const int N = 16;


ll n, a[N][N], dp[1 << N], score[1 << N];

void calc()
{
    int sz = (1 << n);
    for (int mask = 0; mask < sz; mask++)
    {
        ll cur = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                for (int j = i + 1; j < n; j++)
                {
                    if (mask & (1 << j)) {
                        cur += a[i][j];
                    }
                }
            }
        }
        score[mask] = cur;
    }
}

void Solve()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    calc();

    for (int mask = 1; mask < (1 << n) ; mask++)
    {
        for (int sub = mask; sub; sub = (sub - 1)&mask)
        {
            dp[mask] = max(dp[mask], dp[mask ^ sub] + score[sub]);
        }
    }
    cout << dp[(1 << n) - 1] << nl;
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
