#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MX = 1 << 17, inv2 = 499122177, mod = 998244353;

void fwt (int *a, int n, int f = 0) {
	for (int len = 2; len <= n; len *= 2)
		for (int k = 0; k < n; k += len)
			for (int i = k, j = k + len / 2; j < k + len; i++, j++)
				if (f) {
					int x = a[i], y = a[j];
					a[i] = ll(x + y) * inv2 % mod;
					a[j] = ll(x - y + mod) * inv2 % mod;
				} else {
					int x = a[i], y = a[j];
					a[i] = (x + y) % mod;
					a[j] = (x - y + mod) % mod;
				}
}

int m, k, a[MX], b[MX];

ll pot (ll b, int p) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= b) %= mod;
		(b *= b) %= mod;
		p /= 2;
	}
	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> m >> k;
	for (int i = 0; i < k; i++) {
		int c;
		cin >> c;
		b[c] = 1;
	}

	a[0] = 1;
	fwt(a, MX);
	fwt(b, MX);

	int aux = m;
	while (m) {
		if (m & 1)
			for (int i = 0; i < MX; i++)
				a[i] = (ll)a[i] * b[i] % mod;
		for (int i = 0; i < MX; i++)
			b[i] = (ll)b[i] * b[i] % mod;
		m /= 2;
	}

	fwt(a, MX, 1);

	ll q = pot(k, aux);
	ll p = (q - a[0] + mod) % mod;
	cout << p * pot(q, mod - 2) % mod << endl;

	return 0;
}
