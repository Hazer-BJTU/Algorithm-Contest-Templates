#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 200005
using namespace std;
int n,m,a[MAXN],l,r,k;
int f[MAXN],da[MAXN],top;
struct num {
	int index;
	int value;
	num(int index=0,int value=0) {
		this->index=index;
		this->value=value;
	}
}b[MAXN];
bool comp(const num &x,const num &y) {
	return x.value<y.value;
}
struct vertex {
	int key;
	int l;
	int r;
	vertex *lc;
	vertex *rc;
	vertex(int key=0,int l=0,int r=0) {
		this->key=key;
		this->l=l;
		this->r=r;
		this->lc=NULL;
		this->rc=NULL;
	}
};
vector<vertex*>roots;
void update(vertex *p) {
	p->key=p->lc->key+p->rc->key;
	return;
}
void build(vertex *p,int l,int r) {
	p->l=l,p->r=r;
	if (p->l==p->r) {
		p->key=0;
		return;
	}
	int mid=(l+r)>>1;
	p->lc=new vertex();
	p->rc=new vertex();
	build(p->lc,l,mid),build(p->rc,mid+1,r);
	update(p);
	return;
}
void print(vertex *p) {
	printf("[%d,%d]:%d\n",p->l,p->r,p->key);
	if (p->lc!=NULL) print(p->lc);
	if (p->rc!=NULL) print(p->rc);
	return;
}
vertex* add(vertex *p,int pos) {
	if (p->l==p->r) {
		vertex *clone=new vertex(p->key+1,p->l,p->r);
		return clone;
	}
	int mid=(p->l+p->r)>>1;
	vertex *clone=new vertex(p->key,p->l,p->r);
	if (pos<=mid) {
		clone->lc=add(p->lc,pos);
		clone->rc=p->rc;
	} else {
		clone->lc=p->lc;
		clone->rc=add(p->rc,pos);
	}
	update(clone);
	return clone;
}
int ask(vertex *lp,vertex *rp,int k) {
	if (lp->l==lp->r)
		return lp->l;
	int lv=(rp->lc->key)-(lp->lc->key);
	int rv=(rp->rc->key)-(lp->rc->key);
	if (k<=lv) return ask(lp->lc,rp->lc,k);
		else return ask(lp->rc,rp->rc,k-lv);
} 
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d",a+i);
		b[i]=num(i,a[i]);
	}
	sort(b+1,b+n+1,comp);
	top=1,da[b[1].index]=top,f[1]=b[1].value;
	for (int i=2;i<=n;i++) {
		if (b[i].value!=b[i-1].value) top++;
		f[top]=b[i].value;
		da[b[i].index]=top;
	}
	/*
	for (int i=1;i<=n;i++)
		printf("%d:%d\n",i,f[i]);
	for (int i=1;i<=n;i++)
		printf("%d ",da[i]);
	printf("\n");
	*/
	roots.push_back(new vertex());
	build(roots[0],1,n);
	for (int i=1;i<=n;i++)
		roots.push_back(add(roots[i-1],da[i]));
	/*
	for (int i=0;i<=n;i++)
		print(roots[i]),printf("\n");
	*/
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",f[ask(roots[l-1],roots[r],k)]);
	}
	return 0;
}
