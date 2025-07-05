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

ll dp[20][2][2][10][1 << 10];
string s;

ll FuN(int pos, int isstart, int issmall, int mx, int mask)
{
	if (pos >= s.size()) {
		return (__builtin_popcount(mask) == mx);
	}
	if (dp[pos][isstart][issmall][mx][mask] != -1)
		return dp[pos][isstart][issmall][mx][mask];
	ll ret = 0, canbeput = s[pos] - '0';
	if (issmall) canbeput = 9;
	if (isstart) {
		ret += FuN(pos + 1, 1, issmall | (0 < canbeput), mx, mask);
		for (int i = 1; i <= canbeput; i++) {
			ret += FuN(pos + 1, 0, issmall | (i < canbeput), max(mx, i), mask | (1 << i));
		}
	}
	else {
		for (int i = 0; i <= canbeput; i++) {
			ret += FuN(pos + 1, 0, issmall | (i < canbeput), max(mx, i), mask | (1 << i));
		}
	}
	if (issmall)
		dp[pos][isstart][issmall][mx][mask] = ret;
	return ret;
}
void Solve()
{
	cin >> s;
	string ss = "";
	while (ss.size() + s.size() != 19)ss += "0";
	s = ss + s;
	ll ans = FuN(0, 1, 0, 0, 0);
	cout << ans - 1 << nl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	int t, T = 1;
	cin >> T;
	for (t = 1; t <= T; t++)
		Solve();
	return 0;
}
