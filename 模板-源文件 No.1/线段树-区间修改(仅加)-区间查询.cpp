#include <bits/stdc++.h>
#define MAXN 100005
#define lc(x) (2*(x))
#define rc(x) (2*(x)+1)
using namespace std;

int n,m,arr[MAXN],opera,x,y,k;

struct segment_tree
{
	int l;
	int r;
	int length (void)
	{
		return this->r-this->l+1;
	}
	long long sum;
	long long plus;
}tree[4*MAXN];

void update(int p)
{
	tree[p].sum=tree[lc(p)].sum+tree[rc(p)].sum;
}

bool ifspread(int p)
{
	if (tree[p].plus) return true;
	else return false;
}

void spread(int p)
{
	tree[lc(p)].sum=tree[lc(p)].sum+tree[lc(p)].length()*tree[p].plus;
	tree[lc(p)].plus=tree[lc(p)].plus+tree[p].plus;
	
	tree[rc(p)].sum=tree[rc(p)].sum+tree[rc(p)].length()*tree[p].plus;
	tree[rc(p)].plus=tree[rc(p)].plus+tree[p].plus;
	
	tree[p].plus=0;
}

void build(int p,int l,int r)
{
	tree[p].l=l;tree[p].r=r;
	tree[p].plus=0;
	
	if (l==r)
	{
		tree[p].sum=arr[l];
		return;
	}
	
	int mid=(l+r)/2;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	
	update(p);
}

void add(int p,int l,int r,int v)
{
	if (tree[p].l>=l&&tree[p].r<=r)
	{
		tree[p].sum=tree[p].sum+tree[p].length()*v;
		tree[p].plus=tree[p].plus+v;
		return;
	}
	
	if (ifspread(p)) spread(p);
	
	int mid=(tree[p].l+tree[p].r)/2;
	if (l<=mid) add(lc(p),l,r,v);
	if (r>mid) add(rc(p),l,r,v);
	
	update(p);
}

long long ask(int p,int l,int r)
{
	if (tree[p].l>=l&&tree[p].r<=r) return tree[p].sum;
	
	if (ifspread(p)) spread(p);
	
	long long value=0;
	int mid=(tree[p].l+tree[p].r)/2;
	if (l<=mid) value+=ask(lc(p),l,r);
	if (r>mid) value+=ask(rc(p),l,r);
	
	return value;
}

int main ()
{
	scanf("%d%d",&n,&m);
	
	for (int i=1;i<=n;i++) scanf("%d",&arr[i]);
	
	build(1,1,n);
	
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&opera);
		if (opera==1)
		{
			scanf("%d%d%d",&x,&y,&k);
			add(1,x,y,k);
		}
		else if (opera==2)
		{
			scanf("%d%d",&x,&y);
			cout<<ask(1,x,y)<<endl;
		}
	}
	return 0;
}
