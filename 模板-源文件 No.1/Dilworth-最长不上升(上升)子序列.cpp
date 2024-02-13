#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

int que[MAXN];
int longest_notascending_substring(int *a,int n)
{
	int p=0;
	
	que[p]=INT_MAX;
	for (int i=1;i<=n;i++)
	{
		int l=0,r=p,mid;
		
		if (que[r]>=a[i]) que[++p]=a[i];
		else
		{
			while (r!=l+1)
			{
				mid=(r+l)/2;
				if (que[mid]>=a[i]) l=mid;
				else r=mid;
			}
			que[r]=a[i];
		}
	}
	
	return p;
}

int longest_ascending_substring(int *a,int n)
{
	int p=0;
	
	que[p]=INT_MIN;
	for (int i=1;i<=n;i++)
	{
		int l=0,r=p,mid;
		
		if (que[r]<a[i]) que[++p]=a[i];
		else
		{
			while (r!=l+1)
			{
				mid=(l+r)/2;
				if (que[mid]<a[i]) l=mid;
				else r=mid;
			}
			que[r]=a[i];
		}
	}
	
	return p;
}

int n,x,arr[MAXN];
int main ()
{
	while (cin>>x) arr[++n]=x;
	
	cout<<longest_notascending_substring(arr,n)<<'\n';
	cout<<longest_ascending_substring(arr,n);
	return 0;
}
