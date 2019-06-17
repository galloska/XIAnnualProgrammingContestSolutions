#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> sieve(int n){
	vector<int> phi(n+1);
	iota(phi.begin(), phi.end(), 0);
	for(int i = 2; i <= n; ++i){
		if(phi[i] == i){
			for(int j = i; j <= n; j += i){
				phi[j] -= phi[j] / i;
			}
		}
	}
	return phi;
}

vector<int> divisors(int n){
	vector<int> divs;
	for(int i = 1; i*i <= n; ++i){
		if(n % i != 0) continue;
		int j = n / i;
		divs.push_back(i);
		if(j != i) divs.push_back(j);
	}
	return divs;
}

int gcd(int a, int b){
	int r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<int> phi = sieve(n);
	vector<int> cnt(n);
	for(int k : divisors(n)){
		for(int d : divisors(k)){
			cnt[k == n ? 0 : k] += d * phi[n / d];
		}
	}
	for(int k = 0; k < n; ++k){
		int g = gcd(k, n);
		cnt[k] = cnt[g == n ? 0 : g];
	}
	lli sum = 0;
	for(int i = 0; i < n; ++i){
		sum += cnt[i];
		cout << cnt[i] << "\n";
	}
	assert(sum == (lli)n * n);
	return 0;
}
