#include <bits/stdc++.h>
using namespace std;
typedef long long llong;
llong x,y,m,n,L;
llong EXGCD(llong a,llong b,llong &x,llong &y) {
	if (b==0) {
		x=1,y=0;
		return a;
	} else {
		llong x2,y2,ans;
		ans=EXGCD(b,a%b,x2,y2);
		x=y2,y=x2-(a/b)*y2;
		return ans;
	}
}

int main() {
	cin>>x>>y>>m>>n>>L;
	llong a=m-n,b=L,c=y-x;
	llong gcd,k,z;
	gcd=EXGCD(a,b,k,z);
	if (c%gcd!=0) {
		cout<<"Impossible";
		return 0;
	}
	k*=(c/gcd),z*=(c/gcd);
	k%=(b/gcd);
	if (k<0) k+=abs(b/gcd);
	cout<<k;
	return 0;
}
