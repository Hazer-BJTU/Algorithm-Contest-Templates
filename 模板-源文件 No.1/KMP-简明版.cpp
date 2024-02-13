#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;
int n,m,p[MAXN],q[MAXN];
string s,t;
int main() {
	cin>>s>>t;
	s=' '+s,n=s.length()-1;
	t=' '+t,m=t.length()-1;
	p[1]=0;
	for (int i=2;i<=m;i++) {
		int pos=p[i-1]+1;
		while (t[i]!=t[pos]&&pos!=1)
			pos=p[pos-1]+1;
		if (t[i]!=t[pos]) p[i]=0;
			else p[i]=pos;
	}
	q[1]=(s[1]==t[1])?1:0;
	for (int i=2;i<=n;i++) {
		int pos=q[i-1]+1;
		while (s[i]!=t[pos]&&pos!=1)
			pos=p[pos-1]+1;
		if (s[i]!=t[pos]) q[i]=0;
			else q[i]=pos;
	}
	for (int i=1;i<=n;i++)
		if (q[i]==m) printf("%d\n",i-m+1);
	for (int i=1;i<=m;i++)
		printf("%d ",p[i]);
	return 0;
}
