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
/**
 * Monty Hall problem
 * for any n, it is always better to switch the door
 * for n=3, 2/3 probability of win if switch. that was 1/3 before
 *  n door, s open, e eliminate by monty hall
 * (n-s)/(n*(n-s-e)) probability of choosing 1
 * s*(n-s)/(n*(n-s-e)) probability of choosing 1
 * if reamining door is less than s, than switch the remaining, and keep same with other necessary door
 * for 8 4 2, switch 2 and keep same with 2
 * https://codeforces.com/gym/106167/problem/M
**/

void Solve()
{
    ll d, s, e;
    cin >> d >> s >> e;

    double ans, forOne;
    forOne = (1.0 * (d - s)) / (1.0 * (d * (d - s - e)));
    if ((d - s - e) >= s) {
        ans = 1.0 * s * forOne;
    }
    else {
        ll rem = d - s - e;
        ans = rem * forOne;
        ll keepsame = s - rem;
        ans += (keepsame * 1.0) / (d * 1.0);
    }
    cout << fixed << setprecision(10) << ans << nl;
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

