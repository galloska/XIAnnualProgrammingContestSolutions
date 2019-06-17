#include <bits/stdc++.h>
using namespace std;
using ld = double;
using comp = complex<ld>;
const ld PI = acosl(-1.0l);
using lli = long long int;

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

int inverse(int a, int m){
	int r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0/r1), s0 = s1, s1 = si;
		ri = r0%r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

template<int prime, int gen>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(gen, inv * (prime - 1) / (k<<1), prime);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % prime;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % prime;
				X[i + j] = u + v < prime ? u + v : u + v - prime;
				X[i + j + k] = u - v < 0 ? u - v + prime : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, prime);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % prime;
	}
}

template<int prime, int gen>
vector<int> convolution(vector<int> A, vector<int> B){
	int size = A.size();
	ntt<prime, gen>(A, 1), ntt<prime, gen>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % prime;
	ntt<prime, gen>(A, -1);
	return A;
}

const int a = 998244353, b = 985661441, c = 754974721;
const lli a_b = inverse(a, b), a_c = inverse(a, c), b_c = inverse(b, c);
vector<int> convolutionCrt(const vector<int> & A, const vector<int> & B, int p){
	vector<int> P = convolution<a, 3>(A, B);
	vector<int> Q = convolution<b, 3>(A, B);
	vector<int> R = convolution<c, 11>(A, B);
	vector<int> D(P.size());
	for(int i = 0; i < D.size(); ++i){
		int x1 = P[i] % a;
		if(x1 < 0) x1 += a;
		int x2 = a_b * (Q[i] - x1) % b;
		if(x2 < 0) x2 += b;
		int x3 = (a_c * (R[i] - x1) % c - x2) * b_c % c;
		if(x3 < 0) x3 += c;
		D[i] = x1 + a*(x2 + (lli)x3*b % p) % p;
		if(D[i] >= p) D[i] -= p;
		if(D[i] < 0) D[i] += p;
	}
	return D;
}

void bluestein(vector<int> & A, int w, int p){
	int n = A.size();
	int m = nearestPowerOfTwo(2*n-1);
	lli w1 = w, w2 = 1;
	vector<int> P(m), Q(m), B(n);
	for(int k = 0; k < n; ++k, w2 = w2 * w1 % p, w1 = w1 * w % p * w % p){
		B[k] = w2;
		P[k] = (lli)A[k] * B[k] % p;
		Q[k] = inverse(B[k], p);
		if(k) Q[m-k] = Q[k];
	}
	vector<int> R = convolutionCrt(P, Q, p);
	for(int k = 0; k < n; ++k){
 		A[k] = (lli)B[k] * R[k] % p;
	}
}

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
	for(lli p = 2; p*p <= n; ++p){
		int pot = 0;
		while(n % p == 0){
			n /= p;
			pot++;
		}
		if(pot){
			f.emplace_back(p, pot);
		}
	}
	if(n > 1){
		f.emplace_back(n, 1);
	}
	return f;
}

lli findFirstGenerator(lli p){
	lli order = p - 1;
	auto f = factorize(order);
	for(lli x = 1; x < p; x++){
		bool test = true;
		for(auto & factor : f){
			if(powerMod(x, order / factor.first, p) == 1){
				test = false;
				break;
			}
		}
		if(test) return x;
	}
	return -1;
}

vector<int> solve(int n, int p, lli m, vector<int> a){
	int k = (p - 1) / n;
	int g = findFirstGenerator(p);
	assert(g != -1);
	int w = powerMod(g, k, p);
	vector<int> even(n), odd(n);
	for(int i = 0; i < n; ++i){
		if(i & 1) odd[i/2] = a[i];
		else even[i/2] = a[i];
	}
	lli nb = powerMod(n, m / 2, p);
	bluestein(even, w, p);
	bluestein(odd, w, p);
	vector<int> A(n);
	lli w_pw = 1;
	for(int i = 0; i < n; ++i){
		A[i] = even[i] + w_pw * odd[i] % p;
		if(A[i] >= p) A[i] -= p;
		a[i] = a[i] * nb % p;
		A[i] = A[i] * nb % p;
		w_pw = w_pw * w % p;
	}
	if(m % 2 == 0){
		if(m % 4 == 2){
			reverse(a.begin() + 1, a.end());
		}
		return a;
	}else{
		if(m % 4 == 3){
			reverse(A.begin() + 1, A.end());
		}
		return A;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, p; lli m;
	cin >> n >> p >> m;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	vector<int> ans = solve(n, p, m, a);
	for(int & ai : ans){
		cout << ai << " ";
	}
	cout << "\n";
	return 0;
}
