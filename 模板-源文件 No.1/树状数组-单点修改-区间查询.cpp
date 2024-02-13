#include <bits/stdc++.h>
#define MAXN 500005
using namespace std;
int n,m,arr[MAXN],tree[MAXN],opera,x,y;

int lowbit(int x)
{
	return x&(-x);
}

void add(int x,int v)
{
	for (int i=x;i<=n;i+=lowbit(i)) tree[i]+=v;
	return;
}

int ask(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans+=tree[i];
	return ans;
}

int main ()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		cin>>arr[i];
		arr[i]+=arr[i-1];
	}
	
	for (int i=1;i<=m;i++)
	{
		cin>>opera>>x>>y;
		if (opera==1) add(x,y);
		else if (opera==2) cout<<ask(y)-ask(x-1)+arr[y]-arr[x-1]<<'\n';
	}
	return 0;
}
