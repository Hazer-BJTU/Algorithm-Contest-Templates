 #include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
int n,x;
long long dp[MAXN];
int main ()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>x;
		dp[i]=max(dp[i-1]+x,(long long)x);
	}
	
	long long ans=LLONG_MIN;
	for (int i=1;i<=n;i++) ans=max(ans,dp[i]);
	
	cout<<ans;
	return 0;
}
