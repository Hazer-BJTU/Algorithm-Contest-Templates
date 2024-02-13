#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 305
using namespace std;
int n,m,t,u,v;
long long K[MAXN][MAXN],w;

long long quick_power(long long x,long long k)
{
	if (k==0) return 1;
	if (k%2) return quick_power(x,k-1)*x%MOD;
	else
	{
		long long value=quick_power(x,k/2)%MOD;
		return value*value%MOD;
	}
}

long long inverse(long long x)
{
	return quick_power(x,MOD-2);
}

long long determinant(int start)
{
	long long ans=1;
	
	for (int i=start;i<=n;i++)
	{		
		int j;
		long long number=0,coef;
		for (j=i;j<=n;j++)
		{
			if (K[j][i]!=0)
			{
				number=K[j][i];
				break;
			}
		}
		
		if (number==0) {ans=0;break;}
		
		for (int k=i;k<=n;k++)
		{
			if (k==j) continue;
			coef=(-K[k][i]*inverse(K[j][i]))%MOD;
			for (int l=i;l<=n;l++)
				K[k][l]=(K[k][l]+coef*K[j][l])%MOD;
		}
		
		if (j!=i)
		{
			for (int l=start;l<=n;l++) swap(K[i][l],K[j][l]);
			ans*=-1;
		}
	}
	
	for (int i=start;i<=n;i++)
		ans=ans*K[i][i]%MOD;
	
	if (ans<0) ans+=MOD;
	return ans;
}

int main ()
{
	cin>>n>>m>>t;
	for (int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		if (!t)
		{
			K[u][u]=(K[u][u]+w)%MOD;K[v][v]=(K[v][v]+w)%MOD;
			K[u][v]=(K[u][v]-w)%MOD;K[v][u]=(K[v][u]-w)%MOD;
		}
		else
		{
			K[v][v]=(K[v][v]+w)%MOD;
			K[u][v]=(K[u][v]-w)%MOD;
		}
	}
	
	cout<<determinant(2);
	return 0;
}
