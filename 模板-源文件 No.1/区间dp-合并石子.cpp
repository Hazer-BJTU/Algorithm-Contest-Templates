#include <bits/stdc++.h>
#define MAXN 205
using namespace std;
int n,a[MAXN],dp1[MAXN][MAXN],dp2[MAXN][MAXN];
int presum[MAXN];
int main ()
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=n+1;i<=n+n;i++) a[i]=a[i-n];
	for (int i=1;i<=n+n;i++)
	for (int j=1;j<=n+n;j++)
	{
		dp1[i][j]=99999999;
		dp2[i][j]=0;
	}
	for (int i=1;i<=n+n;i++)
	{
		presum[i]=presum[i-1]+a[i];
		dp1[i][i]=0;
		dp2[i][i]=0;
	}
	for (int len=2;len<=n;len++)
	{
		for (int l=1;l<=n+n-len+1;l++)
		{
			int r=l+len-1;
			for (int k=l;k<r;k++)
			{
				dp1[l][r]=min(dp1[l][r],dp1[l][k]+dp1[k+1][r]+presum[r]-presum[l-1]);
				dp2[l][r]=max(dp2[l][r],dp2[l][k]+dp2[k+1][r]+presum[r]-presum[l-1]);
			}
		}
	}
	int ans1=99999999,ans2=0;
	for (int i=1;i<=n;i++)
	{
		ans1=min(ans1,dp1[i][i+n-1]);
		ans2=max(ans2,dp2[i][i+n-1]);
	}
	cout<<ans1<<'\n'<<ans2;
	return 0;
}
