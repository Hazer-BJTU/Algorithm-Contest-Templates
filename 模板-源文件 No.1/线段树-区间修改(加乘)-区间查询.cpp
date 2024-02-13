#include <bits/stdc++.h>
#define MAXN 100005
#define lc(x) (2*(x))
#define rc(x) (2*(x)+1)

int n,m,P,arr[MAXN],opera,x,y,k;

struct segment_tree
{
	int l;
	int r;
	int length(void)
	{
		return this->r-this->l+1;
	}
	long long mult;
	long long plus;
	long long sum;
}tree[4*MAXN];

void update(int p)
{
	tree[p].sum=(tree[lc(p)].sum+tree[rc(p)].sum)%P;
}

bool ifspread(int p)
{
	if (tree[p].mult==1&&tree[p].plus==0) return false;
	else return true;
}

void spread(int p)
{
	tree[lc(p)].sum=(tree[lc(p)].sum*tree[p].mult+tree[lc(p)].length()*tree[p].plus)%P;
	tree[lc(p)].mult=(tree[lc(p)].mult*tree[p].mult)%P;
	tree[lc(p)].plus=(tree[lc(p)].plus*tree[p].mult+tree[p].plus)%P;
	
	tree[rc(p)].sum=(tree[rc(p)].sum*tree[p].mult+tree[rc(p)].length()*tree[p].plus)%P;
	tree[rc(p)].mult=(tree[rc(p)].mult*tree[p].mult)%P;
	tree[rc(p)].plus=(tree[rc(p)].plus*tree[p].mult+tree[p].plus)%P;
	
	tree[p].mult=1;tree[p].plus=0;
}

void build(int p,int l,int r)
{
	tree[p].l=l;tree[p].r=r;
	tree[p].mult=1;tree[p].plus=0;
	
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

void change(char type,int p,int l,int r,int v)
{
	if (tree[p].l>=l&&tree[p].r<=r)
	{
		if (type=='+')
		{
			tree[p].sum=(tree[p].sum+tree[p].length()*v)%P;
			tree[p].plus=(tree[p].plus+v)%P;
		}
		else if (type=='*')
		{
			tree[p].sum=(tree[p].sum*v)%P;
			tree[p].mult=(tree[p].mult*v)%P;
			tree[p].plus=(tree[p].plus*v)%P;
		}
		return;
	}
	
	if (ifspread(p)) spread(p);
	
	int mid=(tree[p].l+tree[p].r)/2;
	if (l<=mid) change(type,lc(p),l,r,v);
	if (r>mid) change(type,rc(p),l,r,v);
	
	update(p);
}

long long ask (int p,int l,int r)
{
	if (tree[p].l>=l&&tree[p].r<=r) return tree[p].sum;
	
	if (ifspread(p)) spread(p);
	
	int mid=(tree[p].l+tree[p].r)/2;
	long long value=0;
	
	if (l<=mid) value+=ask(lc(p),l,r);
	if (r>mid) value+=ask(rc(p),l,r);
	
	return value%P;
}

using namespace std;
int main ()
{
	scanf("%d%d%d",&n,&m,&P);
	
	for (int i=1;i<=n;i++) scanf("%d",&arr[i]);
	
	build(1,1,n);
	
	for (int i=1;i<=m;i++)
	{	
		scanf("%d",&opera);
		if (opera==3)
		{
			scanf("%d%d",&x,&y);
			cout<<ask(1,x,y)<<endl;
		}
		else if (opera==1)
		{
			scanf("%d%d%d",&x,&y,&k);
			change('*',1,x,y,k);
		}
		else if (opera==2)
		{
			scanf("%d%d%d",&x,&y,&k);
			change('+',1,x,y,k);
		}
	}
	return 0;
}
