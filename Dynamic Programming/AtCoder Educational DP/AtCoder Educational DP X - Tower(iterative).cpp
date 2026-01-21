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


const int N = 1e7 + 5;

ll n;

unordered_map<int, ll> dp, ndp;

struct info
{
    ll w, s, v;
    info(ll _w, ll _s, ll _v) {
        w = _w; s = _s; v = _v;
    }
    bool operator < (const info&p)
    {
        if (w + s != p.w + p.s)
            return w + s < p.w + p.s;
        return s < p.s;
    }
};



void Solve()
{
    cin >> n;
    std::vector<info> vec;
    for (int i = 1; i <= n; i++) {
        ll x, y, z;
        cin >> x >> y >> z;
        vec.push_back(info(x, y, z));
    }
    sort(all(vec));

    dp[0] = 0;
    for (auto it : vec)
    {
        ndp = dp;
        for (auto it2 : dp)
        {
            int curW = it2.F;
            ll val = it2.S;

            if (curW <= it.s)
            {
                ndp[curW + it.w] = max(ndp[curW + it.w], val + it.v);
            }
        }
        dp.swap(ndp);
    }
    ll ans = 0;
    for (auto it : dp) {
        ans = max(ans, it.S);
    }

    cout << ans << nl;

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
