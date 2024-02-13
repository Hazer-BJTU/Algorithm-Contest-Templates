#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
struct queries
{
	int index;
	int l;
	int r;
}q[MAXN];
int m,n,a[MAXN],tree[MAXN],pointer,last[MAXN];
long long ans[MAXN];
bool comp(struct queries x,struct queries y)
{
	return x.r<y.r;
}

int lowbit(int x)
{
	return x&(-x);
}

long long ask(int x)
{
	long long ans=0;
	
	while (x!=0)
	{
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}

void add(int x,int k)
{
	while (x<=n)
	{
		tree[x]+=k;
		x+=lowbit(x);
	}
	return;
}

int main ()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].index=i;
	}
	
	sort(q+1,q+m+1,comp);
	
	pointer=0;
	for (int i=1;i<=m;i++)
	{
		while (pointer<q[i].r)
		{
			pointer++;
			if (last[a[pointer]]==0) add(pointer,1);
			else
			{
				add(last[a[pointer]],-1);
				add(pointer,1);
			}
			last[a[pointer]]=pointer;
		}
		
		ans[q[i].index]=ask(q[i].r)-ask(q[i].l-1);
	}
	
	for (int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
