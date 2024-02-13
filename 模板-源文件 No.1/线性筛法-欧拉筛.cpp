#include <bits/stdc++.h>
#define MAXN 6000010
#define MAXM 100000010
using namespace std;
int N,q,x,primelist[MAXN],pointer;
bool isprime[MAXM];
int main ()
{
	memset(isprime,0,sizeof(isprime));
	isprime[1]=1;
	
	scanf("%d%d",&N,&q);
	for (int i=2;i<=N;i++)
	{
		if (!isprime[i]) primelist[++pointer]=i;
		
		for (int j=1;j<=pointer;j++)
		{
			if (i*primelist[j]>N) break;
			isprime[i*primelist[j]]=1;
			if (i%primelist[j]==0) break;
		} 
	}
	
	for (int i=1;i<=q;i++)
	{
		scanf("%d",&x);
		printf("%d\n",primelist[x]);
	}
	return 0;
}
