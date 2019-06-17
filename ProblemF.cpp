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

const int MAXN = 100001;

lli A,B;
lli total[MAXN];

struct Node {
	lli open, closed, ans;

	Node(): open(0), closed(0), ans(0) {}

	Node(lli a, lli b): open(a), closed(b), ans(0) {
		ans = min(open, closed);
		open -= ans;
		closed -= ans;
	}

	Node(const Node &cmp) {
		open = cmp.open;
		closed = cmp.closed;
		ans = cmp.ans;
	}

	Node operator + (const Node& cmp) const {
		Node ans(*this);
		ans.open += cmp.open;
		ans.closed += cmp.closed;
		ans.ans += cmp.ans;
		return ans;
	}

	Node operator ^ (const Node& cmp) const {
		Node ans = *this + cmp;
		ans.open -= min(open, cmp.closed);
		ans.closed -= min(open, cmp.closed);
		ans.ans += min(open, cmp.closed);
		return ans;
	}
};

struct Segment {
	int l,r;
	Node valA;
	Node valB;
	Segment *left, *right;

	Segment(int a, int b): l(a), r(b), valA(), valB(), left(NULL), right(NULL) {}

	void build() {
		if(l == r) {
			valA = Node(A, 0);
			valB = Node(B, 0);
			return;
		}
		int m = (l + r) / 2;
		(left = new Segment(l, m))->build();
		(right = new Segment(m + 1, r))->build();
		valA = left->valA ^ right->valA;
		valB = left->valB ^ right->valB;
	}

	void update(int a, lli v) {
		if(a < l || a > r) return;
		if(a <= l && r <= a) {
			valA = Node(A, v);
			valB = Node(B, v);
			return;
		}
		left->update(a, v);
		right->update(a, v);
		valA = left->valA ^ right->valA;
		valB = left->valB ^ right->valB;
	}

	Node queryA(int a, int b) {
		if(b < l || a > r) return Node();
		if(a <= l && r <= b) return valA;
		return left->queryA(a, b) ^ right->queryA(a, b);
	}

	Node queryB(int a, int b) {
		if(b < l || a > r) return Node();
		if(a <= l && r <= b) return valB;
		return left->queryB(a, b) ^ right->queryB(a, b);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k,q;
	cin>>n>>k>>A>>B>>q;

	Segment *tree = new Segment(1, n);
	tree->build();

	int op,day,cho,p;
	forn(i, q) {
		cin>>op;
		if(op == 1) {
			cin>>day>>cho;
			total[day] += cho;
			tree->update(day, total[day]);
		}	else {
			cin>>p;
			// Not avaliable in days [1, p + k - 1]
			Node A = tree->queryB(1, p - 1);
			Node B = tree->queryA(p + k, n);
			Node ans = A ^ B;
			cout<<ans.ans<<endl;
		}
	}
	return 0;
}
