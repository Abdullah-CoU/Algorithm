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


const int N = 300 + 5;

int n, a[N];

double dp[N][N][N];


// double FuN(int x, int y, int z)
// {
//     if (x + y + z == 0) return 0.0;
//     if (dp[x][y][z] > 0.0) return dp[x][y][z];
//     int tot = (x + y + z);

//     double ret = 0.0;
//     if (x > 0) {
//         ret += (double)(x / tot) * FuN(x - 1, y, z);
//     }
//     if (y > 0) {
//         ret += (double)(y / tot) * FuN(x + 1, y - 1, z);
//     }
//     if (z > 0) {
//         ret += (double)(z / tot) * FuN(x, y + 1, z - 1);
//     }
//     ret += (double)(n / tot);
//     return dp[x][y][z] = tot;
// }
void Solve()
{
    int cnt[4] = {0};
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    dp[0][0][0] = 0.0;

    for (int z = 0; z <= n; z++)
    {
        for (int y = 0; y <= n; y++)
        {
            for (int x = 0; x <= n; x++)
            {
                if (x + y + z == 0)continue;
                if (x + y + z > n) continue;

                double tot = x + y + z;
                double res = (n / tot);

                if (x > 0)
                    res += (x / tot) * dp[x - 1][y][z];
                if (y > 0)
                    res += (y / tot) * dp[x + 1][y - 1][z];
                if (z > 0)
                    res += (z / tot) * dp[x][y + 1][z - 1];

                dp[x][y][z] = res;
            }
        }
    }

    // double ans = FuN(cnt[1], cnt[2], cnt[3]);
    cout << fixed << setprecision(10) << dp[cnt[1]][cnt[2]][cnt[3]] << nl;
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

