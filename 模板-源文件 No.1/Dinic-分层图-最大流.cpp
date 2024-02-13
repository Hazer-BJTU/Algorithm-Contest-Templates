#include <bits/stdc++.h>
#define MAXN 205
using namespace std;
int n,m,s,t,u,v,w;

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

int tier[MAXN];
vector<vertex>graph[MAXN];
bool BFS(int start,int dest)
{
	memset(tier,0,sizeof(tier));
	queue<int>que;
	tier[start]=1;
	que.push(start);
	
	while (!que.empty())
	{
		int now=que.front();que.pop();
		
		for (int i=0;i<graph[now].size();i++)
		{
			int next=graph[now][i].index,cap=graph[now][i].weight;
			
			if (cap>0&&!tier[next])
			{
				que.push(next);tier[next]=tier[now]+1;
				if (next==dest) return true;
			}
		}
	}
	
	return false;
}

int Dinic(int now,int flow,int dest)
{
	if (now==dest) return flow;
	
	int rest=flow,minc;
	for (int i=0;i<graph[now].size();i++)
	{
		int next=graph[now][i].index,cap=graph[now][i].weight;
		int j=graph[now][i].inpos;
		
		if (cap>0&&tier[next]==tier[now]+1)
		{
			minc=Dinic(next,min(rest,cap),dest);
			if (minc==0) tier[next]=0;
			
			graph[now][i].weight-=minc;
			graph[next][j].weight+=minc;
			rest-=minc;
		}
	}
	
	return flow-rest;
}

int main ()
{
	cin>>n>>m>>s>>t;
	for (int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		int lu=graph[u].size(),lv=graph[v].size();
		graph[u].push_back(vertex(v,w,lv));
		graph[v].push_back(vertex(u,0,lu));
	}
	
	int addition=0;
	long long max_flow=0;
	while (BFS(s,t))
		while ((addition=Dinic(s,INT_MAX,t))>0) max_flow+=addition;
	
	cout<<max_flow;
	return 0;
}
