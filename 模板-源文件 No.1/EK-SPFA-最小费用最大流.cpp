#include <bits/stdc++.h>
#define MAXN 5005
using namespace std;
int n,m,s,t,u,v,w,c;
long long max_flow,min_cost;

typedef struct vertex
{
	int index;
	int weight;
	int cost;
	int inpos;
	vertex(int ind=0,int wei=0,int cos=0,int inp=0)
	{
		this->index=ind;
		this->weight=wei;
		this->cost=cos;
		this->inpos=inp;
	}
}vertex;

bool vis[MAXN];
int minc[MAXN],dist[MAXN],pre[MAXN];
vector<vertex>graph[MAXN];
queue<int>que;
bool SPFA(int start,int dest)
{
	memset(vis,true,sizeof(vis));
	while (!que.empty()) que.pop();
	for (int i=1;i<=n;i++) dist[i]=INT_MAX;
	
	minc[start]=INT_MAX;
	dist[start]=0;
	que.push(start);
	vis[start]=false;
	
	while (!que.empty())
	{
		int now=que.front();que.pop();vis[now]=true;
		
		for (int i=0;i<graph[now].size();i++)
		{
			int next=graph[now][i].index,cap=graph[now][i].weight,cost=graph[now][i].cost;
			
			if (cap>0&&cost+dist[now]<dist[next])
			{
				dist[next]=cost+dist[now];
				minc[next]=min(minc[now],cap);
				pre[next]=graph[now][i].inpos;
				if (vis[next])
				{
					que.push(next);
					vis[next]=false;
				}
			}
		}
	}
	
	return dist[dest]!=INT_MAX;
}

void update(int start,int dest)
{
	int now=dest;
	
	while (now!=start)
	{
		int last=graph[now][pre[now]].index,i=graph[now][pre[now]].inpos;
		graph[last][i].weight-=minc[dest];
		graph[now][pre[now]].weight+=minc[dest];
		now=last;
	}
	
	max_flow+=minc[dest];
	min_cost+=dist[dest]*minc[dest];
	
	return;
}


int main ()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&u,&v,&w,&c);
		
		int lu=graph[u].size();
		int lv=graph[v].size();
		graph[u].push_back(vertex(v,w,c,lv));
		graph[v].push_back(vertex(u,0,-c,lu));
	}
	
	while (SPFA(s,t)) update(s,t);
	
	cout<<max_flow<<' '<<min_cost;
	return 0;
}
