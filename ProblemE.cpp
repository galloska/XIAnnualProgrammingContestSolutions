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

string dayOfTheWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int getDay(string a) {
	forn(i, 7)
		if(a == dayOfTheWeek[i])
			return i;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,a,x;
	string day;
	cin>>n>>day>>x;

	int ans = 0, d = getDay(day);
	forn(i, n) {
		cin>>a;
		if(a >= x && d <= 4) ans++;
		d = (d + 1) % 7;
	}
	cout<<ans<<endl;
	return 0;
}
