#include <bits/stdc++.h>
#define MAXN 205
using namespace std;
int n,m,s,t,u,v,w;
long long max_flow;

typedef struct vertex
{
	int index;
	int weight;
	int inpos;
	vertex(int ind=0,int wei=0,int inp=0)
	{
		this->index=ind;
		this->weight=wei;
		this->inpos=inp;
	}
}vertex;

bool vis[MAXN];
int minc[MAXN],pre[MAXN];
vector<vertex>graph[MAXN];
queue<int>que;
bool BFS(int start,int dest)
{
	memset(vis,true,sizeof(vis));
	while (!que.empty()) que.pop();
	
	minc[start]=INT_MAX;
	que.push(start);
	vis[start]=false;
	
	while (!que.empty())
	{
		int now=que.front();que.pop();
		
		for (int i=0;i<graph[now].size();i++)
		{
			int next=graph[now][i].index,cap=graph[now][i].weight;
			
			if (cap>0&&vis[next])
			{
				minc[next]=min(minc[now],cap);
				pre[next]=graph[now][i].inpos;
				que.push(next),vis[next]=false;
				if (next==dest) return true;
			}
		}
	}
	
	return false;
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
	
	return;
}

int main ()
{
	cin>>n>>m>>s>>t;
	for (int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		int lu=graph[u].size();
		int lv=graph[v].size();
		graph[u].push_back(vertex(v,w,lv));
		graph[v].push_back(vertex(u,0,lu));
	}
	
	while (BFS(s,t)) update(s,t);
	
	cout<<max_flow;
	return 0;
}
