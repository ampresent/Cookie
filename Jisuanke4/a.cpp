#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

ll ew,ex,ey,ez,w,x,y,z;
ll X,Y;

ll calc(ll a, ll b){
	return (y*a + z*b + X) - ((ey-a)*y + (ez-b)*z + Y);
}

int main(){

	int T;
	cin >> T;
	while (T--){
		cin >> ew >> ex >> ey >> ez >> w >> x >> y >> z;
		X = ew*w;
		Y = ex*x;

		ll resa,resb;
		for (ll ma=0;ma<=ey;ma++){
			ll min = 0x3f3f3f3f3f3f3f3f;
			ll lb = 0;
			ll rb = ez;
			while (lb <= rb){
				ll mb = (lb+rb)/2;
				ll tmpa = y*ma + z*mb + X;
				ll tmpb = (ey-ma)*y + (ez-mb)*z + Y;
				if (max(tmpa,tmpb) < min){
					min = max(tmpa,tmpb);
					resa = ma;
					resb = mb;
				}
				//prllf("DEBUG %d %d %d\n",ma,mb,tmp);
				if (tmpa-tmpb < 0){
					lb = mb+1;
				}else{
					rb = mb-1;
				}
			}
		}
		ll ans = max(resa*y + resb*z + X ,
				(ey-resa)*y + (ez-resb)*z + Y);
		cout << ans << endl; 
	}
	return 0;
}
