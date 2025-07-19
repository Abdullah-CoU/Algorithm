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


const int N = 4001;

int n, k, dp[2][N], pref[N][N];

int cost(int i, int j)
{
	int sum = pref[j][j] - pref[i - 1][j] - pref[j][i - 1] + pref[i - 1][i - 1];
	return sum >> 1;
}

void DivideAndConquer(int grpNo, int L, int R, int optL, int optR)
{
	if (L > R) return;
	int mid = (L + R) >> 1;

	dp[grpNo % 2][mid] = 1e9;
	int optNow = optL;

	for (int endOfLast = optL; endOfLast <= optR and endOfLast < mid; endOfLast++)
	{
		ll ret = dp[(grpNo - 1) & 1][endOfLast] + cost(endOfLast + 1, mid);
		if (ret < dp[grpNo & 1][mid])
		{
			dp[grpNo & 1][mid] = ret;
			optNow = endOfLast;
		}
	}

	DivideAndConquer(grpNo, L, mid - 1, optL, optNow);
	DivideAndConquer(grpNo, mid + 1, R, optNow, optR);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	for (int j = 0; j < N; j++) {
		dp[0][j] = 1e9;
	}
	dp[0][0] = 0;

	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x;
			cin >> x;
			pref[i][j] = pref[i][j - 1] + pref[i - 1][j] + x - pref[i - 1][j - 1];
		}
	}

	for (int grpNo = 1; grpNo <= k; grpNo++) {
		DivideAndConquer(grpNo, 1, n, 0, n);
	}
	cout << dp[k & 1][n] << nl;
	return 0;
}
