#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;
struct vertex {
	int index;
	int weight;
	vertex(int index=0,int weight=0) {
		this->index=index;
		this->weight=weight;
	}
};
int n,m,s,u,v,w,dist[MAXN];
vector<vertex>graph[MAXN];
queue<int>que;
void SPFA(int start) {
	for (int i=1;i<=n;i++) dist[i]=INT_MAX;
	
	dist[start]=0;
	que.push(start);
	while (!que.empty()) {
		int now=que.front();que.pop();
		for (int i=0;i<graph[now].size();i++) {
			int next=graph[now][i].index,len=graph[now][i].weight;
			if (dist[next]>dist[now]+len) {
				dist[next]=dist[now]+len;
				que.push(next);
			}
		}
	}
}

int main() {
	scanf("%d%d%d",&n,&m,&s);
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		graph[u].push_back(vertex(v,w));
	}
	SPFA(s);
	for (int i=1;i<=n;i++)
		printf("%d ",dist[i]);
	return 0;
}
