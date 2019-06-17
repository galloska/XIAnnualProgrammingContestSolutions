#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using comp = complex<ld>;
const ld PI = acosl(-1.0l);

int main(){
	srand(time(0));
	ld t = rand() % 100;
	ld eval1 = 0;
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	ld w;
	cin >> n >> w;
	comp ans = 0;
	for(int i = 1; i <= n; ++i){
		ld A, phi;
		cin >> A >> phi;
		ans += polar(A, phi);
		eval1 += A * sinl(w*t + phi);
	}
	ld ang = arg(ans);
	if(ang < -1e-9) ang += 2*PI;
	cout << fixed << setprecision(9) << abs(ans) << " " << ang << "\n";
	assert(abs(eval1 - abs(ans) * sinl(w*t + ang)) < 1e-9);
	return 0;
}
