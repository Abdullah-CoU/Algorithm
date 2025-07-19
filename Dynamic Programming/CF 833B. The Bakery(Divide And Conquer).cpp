#include<bits/stdc++.h>
#define ll          long long
#define nl          '\n'
using namespace std;


const int N = 35000 + 1;

int n, k, a[N], dp[2][N],  freq[N], l = 1, r = 0, curCost = 0;

void add(int i)
{
	if (freq[a[i]] == 0)
		curCost++;
	freq[a[i]]++;
}
void remove(int i) {
	freq[a[i]]--;
	if (freq[a[i]] == 0)
		curCost--;
}
int cost(int i, int j)
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

	dp[grpNo & 1][mid] = 0;
	int optNow = optL;

	for (int endOfLast = optL; endOfLast <= optR and endOfLast < mid; endOfLast++)
	{
		int ret = dp[(grpNo - 1) & 1][endOfLast] + cost(endOfLast + 1, mid);
		if (ret > dp[grpNo & 1][mid])
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
		dp[0][j] = 0;
	}
	dp[0][0] = 0;

	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int grpNo = 1; grpNo <= k; grpNo++) {
		DivideAndConquer(grpNo, 1, n, 0, n);
	}
	cout << dp[k & 1][n] << nl;
	return 0;
}
