
/*
 * Today the company has m tasks to complete. The ith task need xi minutes to complete. Meanwhile, this task has a difficulty level yi. The machine whose level below this task¡¯s level yi cannot complete this task. If the company completes this task, they will get (500*xi+2*yi) dollars. 
 * The company has n machines. Each machine has a maximum working time and a level. If the time for the task is more than the maximum working time of the machine, the machine can not complete this task. Each machine can only complete a task one day. Each task can only be completed by one machine. 
 * The company hopes to maximize the number of the tasks which they can complete today. If there are multiple solutions, they hopes to make the money maximum. 
 *
 * authored by wuyihao
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node{
	int x,y;
	bool operator<(const node& n2)const{
		if (x == n2.x)
			return y > n2.y;
		return x > n2.x;
	}
}task[100010],machine[100010];
int cnt[110];

int main(){

	int n,m;
	while (~scanf("%d%d",&n,&m)){
		memset(cnt,0,sizeof cnt);
		for (int i=0;i<n;i++){
			scanf("%d%d",&machine[i].x,&machine[i].y);
		}
		for (int i=0;i<m;i++){
			scanf("%d%d",&task[i].x,&task[i].y);
		}
		sort(machine,machine+n);
		sort(task,task+m);

		long long ans = 0;
		int ans2 = 0;
		for (int i=0,j=0;i<m;i++){
			while (j < n && machine[j].x >= task[i].x){
				//printf("DEBUG %d\n", j);
				cnt[machine[j].y] ++;
				j ++;
			}
			for (int k=task[i].y;k<=100;k++){
				if (cnt[k] > 0){
					//printf("DEBUG %d\n", k);
					ans += task[i].x * 500 + task[i].y * 2;
					cnt[k] --;
					ans2 ++;
					break;
				}
			}
		}
		cout << ans2 << " " << ans << endl;
	}

	return 0;
}
