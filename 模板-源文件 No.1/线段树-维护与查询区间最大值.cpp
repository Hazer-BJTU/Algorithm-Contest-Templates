#include <bits/stdc++.h>
#define MAXN 200005
#define lc(x) (2*(x))
#define rc(x) (2*(x)+1)
using namespace std;
int arr[MAXN],M,D,t,x,pointer;
long long temp;
char opera;

struct segment_tree
{
	int l;
	int r;
	int key;
}tree[4*MAXN];

void update(int p)
{
	int value=-D;
	value=max(value,tree[lc(p)].key);
	value=max(value,tree[rc(p)].key);
	tree[p].key=value;
}

void build(int p,int l,int r)
{
	tree[p].l=l;tree[p].r=r;
	if (l==r)
	{
		tree[p].key=-D;
		return;
	}
	
	int mid=(l+r)/2;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	
	update(p);
	return;
}

void change(int p,int x,int v)
{
	if (tree[p].l==tree[p].r)
	{
		tree[p].key=v;
		return;
	}
	
	int mid=(tree[p].l+tree[p].r)/2;
	if (x<=mid) change(lc(p),x,v);
	else change(rc(p),x,v);
	
	update(p);
	return;
}

int ask(int p,int l,int r)
{
	if (tree[p].l>=l&&tree[p].r<=r) return tree[p].key;
	
	int mid=(tree[p].l+tree[p].r)/2,value=-D;
	if (l<=mid) value=max(value,ask(lc(p),l,r));
	if (r>mid) value=max(value,ask(rc(p),l,r));
	
	return value;
}
int main ()
{
	cin>>M>>D;
	
	build(1,1,M);
	
	pointer=0;
	for (int i=1;i<=M;i++)
	{
		cin>>opera>>x;
		if (opera=='Q')
		{
			t=ask(1,pointer-x+1,pointer);
			cout<<t<<'\n';
		}
		else if (opera=='A')
		{
			temp=((long long)x+t)%D;
			pointer++;
			arr[pointer]=(int)temp;
			change(1,pointer,arr[pointer]);
		}
	}
	return 0;
}
