#include <cstdio>
#include <cstring>
int map[20][20];
int count[20];

int main()
{
    int total = 0;
    scanf("%d",&total);
    while(total--)
    {
        int n = 0,m = 0;
        memset(map,0,sizeof map);
		memset(count,0,sizeof count);
        scanf("%d%d",&n,&m);
        for(int i = 0;i < m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x --;
            y --;
            map[x][y] += 1;
            map[y][x] += 1;
			count[x] ++;
			count[y] ++;
        }
		bool no = false;
		for (int i=0;i<n;i++){
			if (count[i] % 2 != 0){
				no = true;
				break;
			}
		}
		if (no){
			printf("0\n");
			continue;
		}
		int sum = 0;
        for(int i = 0;i < (1<<n);++i)
        {
            no = false;
            for(int j = 0;j < n;++j)
            {
                if((i&(1<<j)) == 0)
                    continue;
                for(int k = 0;k < n;++k)
                {
                    if((i&(1<<k)) == 0)
                        continue;
                    if (map[j][k]){
                        no = true;
                        break;
                    }
                }
                if (no)
                    break;
            }
            if (no) continue;

            for(int j = 0;j < n;++j)
            {
                if(i & (1<<j))
                    continue;
                for(int k = 0;k < n;++k)
                {
                    if(i & (1<<k))
                        continue;
                    if (map[j][k]){
                        no = true;
                        break;
                    }
                }
                if (no)
                    break;
            }
            if (no) continue;

			sum ++;
        }
		printf("%d\n",sum);
    }
    return 0;
} 
