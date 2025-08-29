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

int n, a[N];

void Solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	map<int, ll> ans;
	std::vector<pair<int, int>> last;
	for (int i = 1; i <= n; i++)
	{
		vector<pair<int, int>> cur;
		cur.push_back({a[i], 1});
		for (auto &[x , c] : last) {
			int g = __gcd(x, a[i]);
			if (g == cur.back().first) {
				cur.back().second += c;
			}
			else {
				cur.push_back({g, c});
			}
		}
		for (auto &[x, c] : cur) {
			ans[x] += c;
		}
		last = cur;
	}
	int q;
	cin >> q;
	while (q--)
	{
		int g; cin >> g;
		cout << ans[g] << nl;
	}

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
//https://codeforces.com/problemset/problem/475/D