#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#define lli long long int
#define pii pair<int,int>
#define ppi pair<pii,pii>
#define forn(i, n) for(int i=0;i<n;i++)
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define fi first
#define se second
#define endl '\n'

using namespace std;

const int MAXN = 10001;

int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int A[MAXN];
int B[MAXN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m;
	cin>>n>>m;
	forn(i, n) cin>>A[i];
	forn(i, m) cin>>B[i];

	vi ans(m, 0);
	forn(i, n) {
		int maxi = 0;
		forn(j, m) {
			if(A[i] == B[j]) ans[j] = max(ans[j], maxi + 1);
			if(A[i] > B[j]) maxi = max(maxi, ans[j]);
		}
	}

	int maxi = 0;
	forn(i, m) maxi = max(maxi, ans[i]);
	cout<<maxi * 2<<endl;
	return 0;
}
