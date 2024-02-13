#include <bits/stdc++.h>
#define MAXN 100005
#define F2(x) (1<<(x))
using namespace std;
int N,M,l,r;
int f[MAXN][25],L2[MAXN];
int main ()
{
	L2[0]=-1;
	scanf("%d%d",&N,&M);
	for (int i=1;i<=N;i++)
	{
		scanf("%d",&f[i][0]);
		L2[i]=L2[i/2]+1;
	}
		
	for (int i=1;i<=17;i++)
		for (int j=1;j+F2(i)-1<=N;j++)
			f[j][i]=max(f[j][i-1],f[j+F2(i-1)][i-1]);
	
	for (int i=1;i<=M;i++)
	{
		scanf("%d%d",&l,&r);
		int s=L2[r-l+1];
		
		printf("%d\n",max(f[l][s],f[r-F2(s)+1][s]));
	}
	return 0;
}
