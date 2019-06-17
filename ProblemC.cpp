#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld PI = acosl(-1.0l);

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ld V, R, L, C;
	cin >> V >> R >> L >> C;
	assert(L < 4*R*R*C);
	ld D = sqrtl(4*R*R*L*C - L*L);
	ld t0 = 2.0l * R * L * C / D * atanl(D / L);
	ld t1 = 2.0l * R * L * C / D * (atanl(D / L) + PI);
	auto V_r = [&](ld t){
		return V - V * 2.0 * L / D * expl(-t / (2 * R * C)) * sinl(D / (2 * R * L * C) * t);
	};
	cout << fixed << setprecision(9) << t0 << " " << V_r(t0) << "\n";
	cout << fixed << setprecision(9) << t1 << " " << V_r(t1) << "\n";
	return 0;
}
