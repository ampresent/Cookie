#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2010;
const int MAXM = 60010;
const int MAXQ = 4000000;

struct node{
	int u,v,next,cap,w;
};

int head[MAXN];
node edge[MAXM * 2];
//Nodes on the shortest pathes
bool mark[MAXN];
int gap[MAXN];
int level[MAXN];
int pre[MAXN];
int cur[MAXN];
int que[MAXQ];
int ecnt = 0;
int n,m;
int sos;

void insert(int u,int v,int w,int c){
	edge[ecnt].v = v;
	edge[ecnt].w = w;
	edge[ecnt].cap = c;
	edge[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;

	edge[ecnt].v = u;
	edge[ecnt].w = -w;
	edge[ecnt].cap = 0;
	edge[ecnt].next = head[v];
	head[v] = ecnt;
	ecnt ++;
}

int dist[MAXN];
bool vis[MAXN];

void spfa(){
	memset(dist,0x3f,sizeof dist);
	memset(vis,0,sizeof vis);
	int l = 0, r = 0;

	que[r++] = 1;
	dist[1] = 0;
	while (l < r){
		int u = que[l];
		l ++;

		vis[u] = false;
		for (int vv=head[u];vv!=-1;vv=edge[vv].next){
			int v = edge[vv].v;
			//printf("DEBUG %d ==> %d\n",u,v);
			if (dist[v] > dist[u] + edge[vv].w){
				dist[v] = dist[u] + edge[vv].w;

				if (!vis[v]){
					vis[v] = true;
					que[r] = v;
					//printf("DEBUG v = %d\n",v);
					r ++;
				}
			}
		}
	}
}

void dfs(int v){
	mark[v] = true;
	for (int uu = head[v];uu!=-1;uu=edge[uu].next){
		int u = edge[uu].v;
		if (!mark[u] && dist[u]-edge[uu].w==dist[v]){
			dfs(u);
		}
	}
}

int sap(int s,int t){
	memset(level, 0, sizeof level);
	memset(gap, 0, sizeof gap);
	memset(pre, -1, sizeof pre);
	for (int i=0;i<=n;i++){
		cur[i] = head[i];
	}
	int maxflow = 0;
	int aug = -1;
	int u=pre[s]=s;
	//A dfs that borrowed level from bfs
	while (level[s] < n){
loop:
		//printf("DEBUG u = %d\n",u);
		for (int &i=cur[u];i!=-1;i=edge[i].next){
			int v = edge[i].v;
			if (!mark[v]) continue;
			if (edge[i].cap && level[v]+1==level[u]){
				aug==-1?(aug=edge[i].cap):(aug=min(aug,edge[i].cap));
				pre[v] = u;
				u = v;
				//printf("DEBUG %d ==> %d\n",u,v);
				if (v == t){
					maxflow += aug;
					for (u=pre[v];v!=s;v=u,u=pre[u]){
						//printf("DEBUG (%d ==> %d) -= aug\n", u,v);
						edge[cur[u]].cap -= aug;
						edge[cur[u]^1].cap += aug;
					}
					aug = -1;
				}
				goto loop;
			}
		}
		int minlevel = n;
		for (int i=head[u];i!=-1;i=edge[i].next){
			int v = edge[i].v;
			if (!mark[v]) continue;
			if (edge[i].cap && minlevel>level[v]){
				cur[u] = i;
				minlevel = level[v];
			}
		}
		if ((--gap[level[u]]) == 0) break;
		level[u] = minlevel + 1;
		gap[level[u]] ++;
		//backtrack of recurrence
		u = pre[u];
	}
	return maxflow;
}

struct dd{
	int a,b;
}dist2[MAXN];

void spfa2(){
	memset(dist2, 0x3f, sizeof dist2);
	memset(vis,0,sizeof vis);

	int l = 0;
	int r = 0;

	dist2[1].a = dist2[1].b = 0;
	
	que[r ++] = 1;

	while (l < r){
		int u = que[l];
		l ++;
		if (l == MAXQ){
			l = 0;
		}
		vis[u] = false;
		for (int vv=head[u];vv!=-1;vv=edge[vv].next){
			int v = edge[vv].v;
			if (dist2[v].a > dist2[u].a + edge[vv].w ||
					(dist2[v].a == dist2[u].a + edge[v].w &&
					dist2[v].b > dist2[u].b + 1))
			{
				dist2[v].a = dist2[u].a + edge[vv].w;
				dist2[v].b = dist2[u].b + 1;
				//printf("DEBUG %d ==> %d\n",u,v);
				if (!vis[v]){
					vis[v] = true;
					que[r] = v;
					r ++;
					if (r == MAXQ){
						r = 0;
					}
				}
			}
		}
	}
}

void dfs2(int v,int l,bool s){
	mark[v] = true;
	if (v == 1 && s){
		sos = min(sos,l);
	}
	for (int uu=head[v];uu!=-1;uu=edge[uu].next){
		int u = edge[uu].v;
		if (!mark[u] && dist2[u].a-edge[uu].w == dist2[v].a){
			if (dist2[u].b+1 == dist2[v].b)
				dfs2(u, l+1, s);
			else
				dfs2(u, l+1, false);
		}
	}
}

int main(){
	freopen("1007.in","r",stdin);
	while (~scanf("%d%d",&n,&m)){
		memset(head, -1, sizeof head);
		memset(mark, 0, sizeof mark);
		sos = 0x3f3f3f3f;
		ecnt = 0;
		for (int i=0;i<m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			insert(u,v,w,1);
		}
		//spfa();
		spfa2();
		dfs2(n, 0, true);
		int ans1 = sap(1,n);
		printf("%d %d\n",ans1, m - sos);
	}
	return 0;
}
