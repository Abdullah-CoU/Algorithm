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


const int N = 500 + 5;

ll cost[N][N], dis[N][N];

void Solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dis[i][j] = 1e18;
		}
	}
	for (int i = 1; i <= m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		dis[a][b]  = min(dis[a][b], c);
		dis[b][a]  = min(dis[b][a], c);
	}
	for (int i = 1; i <= n; i++) dis[i][i] = 0;

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (dis[i][j] > dis[i][k] + dis[k][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}

	while (q--) {
		int a, b; cin >> a >> b;
		if (dis[a][b] == 1e18)
			dis[a][b] = -1;
		cout << dis[a][b] << endl;
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
