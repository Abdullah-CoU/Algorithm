#include<bits/stdc++.h>
#define ll                  long long
using namespace std;


const int N = 2e5 + 5;


struct manacher
{
	std::vector<int> p;
	void build(string s)
	{
		int n = s.size();
		string t;
		for (int i = 0; i < n; i++) {
			t += string("#") + s[i];
		}
		t += "#";
		n = t.size();
		p.assign(n, 1);
		int l = 1, r = 1;
		for (int i = 0; i < n; i++) {
			p[i] = max(0, min(r - i, p[l + r - i]));
			while (i - p[i] >= 0 && i + p[i] < n && s[i - p[i]] == s[i + p[i]]) {
				p[i]++;
			}
			if (i + p[i] > r) {
				l = i - p[i];
				r = i + p[i];
			}
		}
	}
	int getLongestPalindrome(int center, bool odd) {
		int pos = 2 * center + 1 + (!odd);
		return p[pos] - 1;
	}
	bool checkPalindrome(int l, int r) {
		if (r - l + 1 <= getLongestPalindrome((l + r) / 2, l % 2 == r % 2)) {
			return 1;
		}
		return 0;
	}
};
void Solve(int t)
{
	;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, T = 1;
	// cin >> T;
	for (t = 1; t <= T; t++)
		Solve(t);
	return 0;
}