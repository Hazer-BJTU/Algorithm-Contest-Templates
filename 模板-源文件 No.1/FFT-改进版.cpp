#include <bits/stdc++.h>
#define MAXN 2100000
#define PI 3.14159265359 
using namespace std;
struct comp {
	double real;
	double image;
	comp(double real=0.0,double image=0.0) {
		this->real=real;this->image=image;
	}
}a[MAXN],b[MAXN];
comp operator + (const comp &a,const comp &b) {
	return comp(a.real+b.real,a.image+b.image);
}
comp operator - (const comp &a,const comp &b) {
	return comp(a.real-b.real,a.image-b.image);
}
comp operator * (const comp &a,const comp &b) {
	return comp(a.real*b.real-a.image*b.image,
		a.real*b.image+a.image*b.real);
}
comp unit_root(int k,int n) {
	return comp(cos(2.0*k*PI/n),sin(2.0*k*PI/n));
}
comp promote(int n) {
	return comp((double)n,0.0);
}
int bit_reverse(int n,int m) {
	int ans=0;
	for (int i=1;i<=m;i++)
		ans=(ans<<1)+(n&1),n>>=1;
	return ans;
}

int N,M,L=1,lgL=0,x,r[MAXN];
void DFT(comp *A,int n,int lgn,bool form) {
	for (int i=0;i<n;i++)
		if (i<r[i]) swap(A[i],A[r[i]]);
	
	int step=1;
	comp wm,w,temp;
	for (int s=1;s<=lgn;s++) {
		step<<=1;
		if (form) wm=unit_root(1,step);
			else wm=unit_root(-1,step);
		
		for (int k=0;k<n;k+=step) {
			w=comp(1.0,0.0);
			for (int j=0;j<step/2;j++) {
				temp=w*A[k+j+step/2];
				A[k+j+step/2]=A[k+j]-temp;
				A[k+j]=A[k+j]+temp;
				w=w*wm;
			}
		}
	}
	if (!form) for (int i=0;i<n;i++)
		A[i].real/=n,A[i].image/=n;
	return;
}

int main() {
	cin>>N>>M;
	for (int i=0;i<=N;i++)
		scanf("%d",&x),a[i]=promote(x);
	for (int i=0;i<=M;i++)
		scanf("%d",&x),b[i]=promote(x);
	while(L<2*max(N,M))
		L*=2,lgL++;
	for (int i=0;i<L;i++)
		r[i]=bit_reverse(i,lgL); 
	
	DFT(a,L,lgL,1);
	DFT(b,L,lgL,1);
	
	for (int i=0;i<L;i++)
		a[i]=a[i]*b[i];
	
	DFT(a,L,lgL,0);
	for (int i=0;i<=N+M;i++)
		printf("%d ",(int)(a[i].real+0.5));
	return 0;
}
