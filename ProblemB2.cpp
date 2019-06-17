#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 998244353;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

lli powerMod(lli a, lli b){
	lli ans = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans % mod;
}

void xorTransform(vector<int> & A, int inv){
	int n = A.size();
	assert((n & (n - 1)) == 0);
	for(int k = 1; k < n; k <<= 1){
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				A[i + j] = u + v < mod ? u + v : u + v - mod;
				A[i + j + k] = u - v < 0 ? u - v + mod : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, mod - 2);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % mod;
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, k;
	cin >> m >> k;
	vector<int> A;
	for(int i = 1; i <= k; ++i){
		int ci;
		cin >> ci;
		if(ci >= A.size()) A.resize(ci + 1);
		A[ci] = 1;
	}
	A.resize(nearestPowerOfTwo(A.size()));
	xorTransform(A, 1);
	for(int & ai : A){
		ai = powerMod(ai, m);
	}
	xorTransform(A, -1);
	int q = (lli)A[0] * powerMod(k, -m) % mod;
	int p = (1 - q) % mod;
	if(p < 0) p += mod;
	cout << p << "\n";
	return 0;
}
