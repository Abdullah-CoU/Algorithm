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


const int N = 1e5 + 5;

ll n, k, a[N], dp[22][N], opt[22][N], freq[N], l = 1, r = 0, curCost = 0;

void add(int i)
{
	curCost += freq[a[i]];
	freq[a[i]]++;
}
void remove(int i) {
	freq[a[i]]--;
	curCost -= freq[a[i]];
}
ll cost(int i, int j)
{
	while (j > r) add(++r);
	while (l > i) add(--l);
	while (j < r) remove(r--);
	while (i > l) remove(l++);
	return curCost;
}

void DivideAndConquer(int grpNo, int L, int R, int optL, int optR)
{
	if (L > R) return;
	int mid = (L + R) >> 1;

	dp[grpNo][mid] = 1e18;
	int optNow = optL;

	for (int endOfLast = optL; endOfLast <= optR and endOfLast < mid; endOfLast++)
	{
		ll ret = dp[grpNo - 1][endOfLast] + cost(endOfLast + 1, mid);
		if (ret < dp[grpNo][mid])
		{
			dp[grpNo][mid] = ret;
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
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][j] = 1e18;
		}
	}
	dp[0][0] = 0;

	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	// for (int grpNo = 1; grpNo <= k; grpNo++)
	// {
	// 	for (int pos = 1; pos <= n; pos++)
	// 	{
	// 		for (int endOfLast = opt[grpNo][pos - 1]; endOfLast < pos; endOfLast++)
	// 		{
	// 			// dp[grpNo][pos] = min(dp[grpNo][pos], dp[grpNo - 1][endOfLast] + cost(endOfLast + 1, pos));
	// 			ll ret = dp[grpNo - 1][endOfLast] + cost(endOfLast + 1, pos);
	// 			if (ret < dp[grpNo][pos]) {
	// 				dp[grpNo][pos] = ret;
	// 				opt[grpNo][pos] = endOfLast;
	// 			}
	// 		}
	// 	}
	// }
	for (int grpNo = 1; grpNo <= k; grpNo++) {
		DivideAndConquer(grpNo, 1, n, 0, n);
	}
	cout << dp[k][n] << nl;
	return 0;
}
