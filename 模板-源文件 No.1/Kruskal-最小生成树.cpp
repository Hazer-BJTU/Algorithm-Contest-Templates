#include <bits/stdc++.h>
#define MAXN 5005
using namespace std;
int N,M,X,Y,Z,father[MAXN];
long long ans;

int find_father(int x)
{
	if (father[x]==x) return x;
	else return father[x]=find_father(father[x]);
}

typedef struct vertex
{
	int x;
	int y;
	int weight;
	vertex(int X=0,int Y=0,int Weight=0)
	{
		this->x=X;this->y=Y;this->weight=Weight;
	}
}vertex;

struct comp
{
	bool operator () (vertex a,vertex b)
	{
		return a.weight>b.weight;
	}
};

priority_queue< vertex,vector<vertex>,comp >que;

int main ()
{
	cin>>N>>M;
	for (int i=1;i<=M;i++)
	{
		cin>>X>>Y>>Z;
		que.push(vertex(X,Y,Z));
	}
	
	for (int i=1;i<=N;i++) father[i]=i;
	
	while (!que.empty())
	{
		vertex now=que.top();que.pop();
		
		if (find_father(now.x)==find_father(now.y)) continue;
		
		father[find_father(now.x)]=find_father(now.y);
		ans+=now.weight;
	}
	
	bool mark=true;
	for (int i=1;i<=N;i++)
	{
		if (find_father(i)!=find_father(1))
		{
			mark=false;
			break;
		}
	}
	
	if (mark) cout<<ans;
	else cout<<"orz";
	return 0;
}
