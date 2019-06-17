#include <bits/stdc++.h>

using namespace std;

int sumDigit (string &s) {
	int ans = 0;
	for (char c : s)
		if (c != '*')
			ans += c - '0';
	return ans % 9;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int n, m, k;
	string a, b, p;

	cin >> n >> m >> k;
	cin >> a >> b >> p;

	int ans = sumDigit(a) * sumDigit(b) - sumDigit(p);
	ans = (ans % 9 + 9) % 9;
	if (!ans) ans += 9;
	cout << ans << endl;

	return 0;
}
