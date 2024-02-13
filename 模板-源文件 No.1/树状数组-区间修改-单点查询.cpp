#include <bits/stdc++.h>
#define MAXN 500005
using namespace std;
int n,m,arr[MAXN],tree[MAXN],opera,x,y,k;

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
	for (int i=1;i<=n;i++) cin>>arr[i];
	
	for (int i=1;i<=m;i++)
	{
		cin>>opera;
		if (opera==1)
		{
			cin>>x>>y>>k;
			add(x,k);
			add(y+1,-k);
		}
		else if (opera==2)
		{
			cin>>x;
			cout<<arr[x]+ask(x)<<'\n';
		}
	}
	return 0;
}
