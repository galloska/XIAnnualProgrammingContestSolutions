#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 1000001;

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	string cad;
	cin>>cad;
	sort(cad.begin(), cad.end());
	cout<<cad<<endl;
	return 0;
}
