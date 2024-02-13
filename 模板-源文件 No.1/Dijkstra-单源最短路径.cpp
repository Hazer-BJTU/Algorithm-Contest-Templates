#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n,m,s,u,v,w;
class vertex
{
	public:
		int index;
		int weight;
		vertex (int ind=0,int wei=0)
		{
			this->index=ind;this->weight=wei;
		}
};
struct comp
{
	bool operator () (const vertex &a,const vertex &b)
	{
		return a.weight>b.weight;
	}
};
vector<vertex>graph[MAXN];
priority_queue< vertex,vector<vertex>,comp >que;

int dist[MAXN];
bool vis[MAXN];
void Dijkstra (int index)
{
	memset(vis,true,sizeof(vis));
	for (int i=1;i<=n;i++) dist[i]=INT_MAX;
	
	dist[index]=0;
	que.push(vertex(index,0));
	while (!que.empty())
	{
		int least=que.top().index;que.pop();
		
		if (!vis[least]) continue;
		vis[least]=false;
		
		for (int i=0;i<graph[least].size();i++)
		{
			int next=graph[least][i].index,weight=graph[least][i].weight;
			
			if (dist[next]>dist[least]+weight)
			{
				dist[next]=dist[least]+weight;
				que.push(vertex(next,dist[next]));
			}
		}
	}
}
int main ()
{
	scanf("%d%d%d",&n,&m,&s);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		graph[u].push_back(vertex(v,w));
	}
	
	Dijkstra(s);
	
	for (int i=1;i<=n;i++) printf("%d ",dist[i]);
	return 0;
}
