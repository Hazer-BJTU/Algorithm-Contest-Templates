#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
struct segment_tree {
	int l;
	int r;
	int key;
}tree[4*MAXN];
int n,q,l,r,v,a[MAXN];
int lc(int x) {
	return 2*x;
}
int rc(int x) {
	return 2*x+1;
}
void build(int p,int l,int r) {
	tree[p].l=l,tree[p].r=r;
	if (l==r) {
		tree[p].key=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	tree[p].key=min(tree[lc(p)].key,tree[rc(p)].key);
	return;
}
int ask(int p,int l,int r,int v) {
	if (tree[p].l==tree[p].r) {
		if (tree[p].key<=v) return tree[p].l;
		else return -1;
	}
	if (tree[p].l>=l&&tree[p].r<=r&&tree[p].key>v) return -1;
	int mid=(tree[p].l+tree[p].r)/2,temp=-1;
	if (l<=mid) temp=ask(lc(p),l,r,v);
	if (temp!=-1) return temp;
	if (r>mid) temp=ask(rc(p),l,r,v);
	return temp;
}
int main () {
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	cin>>q;
	for (int i=1;i<=q;i++) {
		cin>>l>>r>>v;
		cout<<ask(1,l,r,v)<<'\n';
	}
	return 0;
}
