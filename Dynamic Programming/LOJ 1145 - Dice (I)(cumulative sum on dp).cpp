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
#define MOD         100000007
using namespace std;


const int N = 2e5 + 5;
int dp[2][15002], csum[2][15002];

void Solve()
{
    int n, k, W;
    cin >> n >> k >> W;

    for (int i = 1; i <= W; i++)
    {
        dp[(n + 1) & 1][i] = 0;
        csum[(n + 1) & 1][i] = 1;
    }
    dp[(n + 1) & 1][0] = 1;
    csum[(n + 1) & 1][0] = 1;

    for (int i = n; i >= 1; i--)
    {
        dp[i & 1][0] = csum[i & 1][0] = 0;
        for (int j = 1; j <= W; j++)
        {
            if (j - k - 1 >= 0) {
                dp[i & 1][j] = csum[(i + 1) & 1][j - 1] -  csum[(i + 1) & 1][ j - k - 1] + MOD;
            }
            else
                dp[i & 1][j] = csum[(i + 1) & 1][j - 1];
            dp[i & 1][j] %= MOD;
            csum[i & 1][j] = dp[i & 1][j] + csum[i & 1][j - 1];
            csum[i & 1][j] %= MOD;
        }
    }
    cout << (dp[1][W] + MOD) % MOD << nl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, T = 1;
    cin >> T;
    for (t = 1; t <= T; t++) {
        cout << "Case " << t << ": ";
        Solve();
    }
    return 0;
}
