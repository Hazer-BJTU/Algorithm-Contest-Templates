#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
int n,m,x,y,verwei[MAXN],compwei[MAXN],dp[MAXN];
vector<int>graph[MAXN],DAG[MAXN];

int num,dfn[MAXN],low[MAXN],stac[MAXN],top;
vector<int>comp_mem[MAXN];
int counter,comp[MAXN];
bool instac[MAXN];
void Tarjan (int x)
{
	dfn[x]=low[x]=++num;
	stac[++top]=x,instac[x]=true;
	
	for (int i=0;i<graph[x].size();i++)
	{
		int next=graph[x][i];
		
		if (!dfn[next])
		{
			Tarjan(next);
			low[x]=min(low[x],low[next]);
		}
		else if (instac[next])
			low[x]=min(low[x],dfn[next]);
	}
	
	if (dfn[x]==low[x])
	{
		int y;
		
		counter++;
		do
		{
			y=stac[top--],instac[y]=false;
			comp[y]=counter;
			comp_mem[counter].push_back(y);
			compwei[counter]+=verwei[y];
		}
		while (x!=y);
	}
}

int indegree[MAXN];
queue<int>que;
vector<int>ans;
void Topology_sort(void)
{
	for (int i=1;i<=counter;i++)
		for (int j=0;j<DAG[i].size();j++)
			indegree[DAG[i][j]]++;
	
	for (int i=1;i<=counter;i++)
		if (!indegree[i]) que.push(i);
		
	while (!que.empty())
	{
		int now=que.front();que.pop();
		
		for (int i=0;i<DAG[now].size();i++)
		{
			int next=DAG[now][i];
			
			indegree[next]--;
			if (!indegree[next]) que.push(next);
		}
		
		ans.push_back(now);
	}
}

int main ()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&verwei[i]);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		graph[x].push_back(y);
	}
	
	for (int i=1;i<=n;i++)
		if (!dfn[i]) Tarjan(i);
		
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<graph[i].size();j++)
		{
			int next=graph[i][j];
			
			if (comp[i]!=comp[next]) 
				DAG[comp[i]].push_back(comp[next]);
		}
	}
	
	Topology_sort();
	
	for (int i=0;i<ans.size();i++) dp[ans[i]]=compwei[ans[i]];
	for (int i=0;i<ans.size();i++)
	{
		int now=ans[i];
		
		for (int j=0;j<DAG[now].size();j++)
		{
			int next=DAG[now][j];
			
			dp[next]=max(dp[next],dp[now]+compwei[next]);
		}
	}
	
	int final_ans=0;
	for (int i=1;i<=counter;i++) final_ans=max(final_ans,dp[i]);
	
	cout<<final_ans;
	return 0;
}
