#include <bits/stdc++.h>
#define MAXN 40005
using namespace std;
int n,arr[MAXN],position[MAXN];
long long presum[MAXN],backsum[MAXN];
bool comp(int x,int y)
{
	return x>y;
}
int main ()
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",arr+i);
		
		sort(arr+1,arr+n+1,comp);
		
		presum[0]=0;
		for (int i=1;i<=n;i++) presum[i]=presum[i-1]+arr[i];
		backsum[n+1]=0;
		for (int i=n;i>=1;i--) backsum[i]=backsum[i+1]+arr[i];
		
		if (presum[n]%2) {printf("No\n");continue;}
		
		int pointer=1;
		for (int i=n;i>=1;i--)
		{
			while (arr[pointer]>i&&pointer<=n) pointer++;
			position[i]=pointer;
		}
		
		bool mark=true;
		for (int i=1;i<=n;i++)
		{
			long long temp=0;
			if (i+1<=n)
			{
				int y=max(position[i],i+1);
				temp=(y-i-1)*i+backsum[y];
			}
			if (presum[i]>i*(i-1)+temp)
			{
				mark=false;
				break;
			}
		}
		
		if (mark) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
