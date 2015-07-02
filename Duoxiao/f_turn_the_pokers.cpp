#include <algorithm>
#include <cstdio>
using namespace std;

int near(int l,int r,int x){
	if (x <= l){
		return l;
	}else if (x >= r){
		return r;
	}else{
		if ((x&1) == (r&1))
			return x;
		else
			return x-1;
	}
}

int main(){
	int n,m;
	while (~scanf("%d%d",&n,&m)){
		int x,ymi,yma;
		scanf("%d",&ymi);
		yma = ymi;
		for (int i=1;i<n;i++){
			scanf("%d",&x);

			int yy = near(ymi,yma,m-x);
			yma = m*2 - yy - x;

			yy = near(ymi,yma,x);
			ymi = abs(x-yy);

		}
		long long ans = 0;
		long long c = 1;
		for (int i=0;i<=yma;i++){
			if ((i&1) == (ymi&1) && i>=ymi)
				ans = (ans + c)%1000000009;
			c = c*(m-i)/(i+1);
		}

		ans %= 1000000009;
		printf("%d\n",int(ans));
	}
	return 0;
}
