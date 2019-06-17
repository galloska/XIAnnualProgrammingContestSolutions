#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb(x) push_back(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 200005;
int n = 1, q, u, v, last = 0, lvl[MX], p[MX][18];
char op;

int LCA (int u, int v) {
	if (lvl[u] < lvl[v])
		swap(u, v);

	for (int j = 0; j < 18; j++)
		if ((lvl[u] - lvl[v]) & (1 << j))
			u = p[u][j];

	if (u == v)
		return u;

	for (int j = 17; j >= 0; j--)
		if (p[u][j] != p[v][j])
			u = p[u][j], v = p[v][j];

	return p[u][0];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> q;

	for (int j = 0; j < 18; j++)
		p[1][j] = 1;

	while (q--) {
		cin >> op;

		if (op == '1') {
			cin >> u;
			u = (u + last) % n + 1;

			p[++n][0] = u;
			lvl[n] = lvl[u] + 1;
			for (int j = 1; j < 18; j++)
				p[n][j] = p[p[n][j-1]][j-1];

			last = lvl[n] + 1;
		} else {
			cin >> u >> v;
			u = (u + last) % n + 1;
			v = (v + last) % n + 1;

			int lca = LCA(u, v);
			last = lvl[u] + lvl[v] - 2 * lvl[lca] + 1;
		}

		cout << last << endl;
	}

	return 0;
}
