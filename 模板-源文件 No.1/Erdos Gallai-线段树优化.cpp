#include <bits/stdc++.h>
#define MAXN 40005
#define lc(x) (2*(x))
#define rc(x) (2*(x)+1)
using namespace std;
int n,arr[MAXN];
long long presum[MAXN],backsum[MAXN];
bool comp(int x,int y)
{
	return x>y;
}

struct segment_tree
{
	int l;
	int r;
	int key;
}tree[4*MAXN];

void update(int p)
{
	tree[p].key=min(tree[lc(p)].key,tree[rc(p)].key);
}

void build(int p,int l,int r)
{
	tree[p].l=l,tree[p].r=r;
	if (l==r)
	{
		tree[p].key=arr[l];
		return;
	}
	
	int mid=(l+r)/2;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	
	update(p);
}

int ask(int p,int l,int r,int v)
{
	if (tree[p].l==tree[p].r)
	{
		if (tree[p].key<=v) return tree[p].l;
		else return n+1;
	}
	
	if (tree[p].l>=l&&tree[p].r<=r&&tree[p].key>v) return n+1;
	
	int mid=(tree[p].l+tree[p].r)/2,temp=n+1;
	
	if (l<=mid) temp=ask(lc(p),l,r,v);
	if (temp!=n+1) return temp;
	if (r>mid) temp=ask(rc(p),l,r,v);
	return temp;
}

int main ()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",arr+i);
		
		sort(arr+1,arr+n+1,comp);
		
		presum[0]=0;
		for (int i=1;i<=n;i++) presum[i]=presum[i-1]+arr[i];
		backsum[n+1]=0;
		for (int i=n;i>=1;i--) backsum[i]=backsum[i+1]+arr[i];
		
		build(1,1,n);
		
		if (presum[n]%2) {printf("No\n");continue;}
		
		bool mark=true;
		for (int i=1;i<=n;i++)
		{
			long long temp=0;
			if (i+1<=n)
			{
				int y=ask(1,i+1,n,i);
				temp=(y-i-1)*i+backsum[y];
			}
			if (presum[i]>i*(i-1)+temp)
			{
				mark=false;
				break;
			}
		}
		
		if (mark) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
