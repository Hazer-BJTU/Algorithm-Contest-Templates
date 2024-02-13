#include <bits/stdc++.h>
#define MAXN 2100000
#define MOD 998244353 //2^23*119+1
using namespace std;
typedef long long llong;
llong a[MAXN],b[MAXN],na[MAXN],nb[MAXN];
int ans[MAXN];

llong quick_power (llong a,llong b,llong mod)
{
	if (b==1) return a%mod;
	if (b%2) return quick_power(a,b-1,mod)*a%mod;
	else
	{
		llong temp=quick_power(a,b/2,mod);
		return temp*temp%mod;
	}
}

llong primitive_root (int m,bool form)
{
	if (form) return quick_power(3,(MOD-1)/m,MOD);
	else return quick_power(332748118,(MOD-1)/m,MOD);
}

int bit_reverse(int n,int m)
{
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		ans*=2;
		ans+=n%2;
		n/=2;
	}
	return ans;
}

void NTT(llong *a,llong *A,int len,int lglen,bool form)
{
	for (int i=0;i<len;i++) A[bit_reverse(i,lglen)]=a[i];
	
	int step=1;
	llong p_m,p,temp;
	for (int s=1;s<=lglen;s++)
	{
		step*=2;
		p_m=primitive_root(step,form);
		
		for (int k=0;k<len;k+=step)
		{
			p=1;
			for (int j=0;j<step/2;j++)
			{
				temp=p*A[k+j+step/2]%MOD;
				A[k+j+step/2]=(A[k+j]-temp)%MOD;
				A[k+j]=(A[k+j]+temp)%MOD;
				p=p*p_m%MOD;
			}
		}
	}
	
	if (!form)
	{
		llong inv=quick_power(len,MOD-2,MOD);
		for (int i=0;i<len;i++) A[i]=A[i]*inv%MOD;
	}
	
	return;
}

string x,y;
int main ()
{
	cin>>x>>y;
	for (int i=x.length()-1;i>=0;i--)
		a[x.length()-i-1]=x[i]-'0';
	for (int i=y.length()-1;i>=0;i--)
	    b[y.length()-i-1]=y[i]-'0';
	    
	int len=1,lglen=0;
	while (len<max(x.length(),y.length())) len*=2,lglen++;
	len*=2,lglen++;
	
	NTT(a,na,len,lglen,1);
	NTT(b,nb,len,lglen,1);
	
	for (int i=0;i<len;i++) na[i]=na[i]*nb[i]%MOD;
	
	NTT(na,nb,len,lglen,0);
	
	for (int i=0;i<len;i++)
	{
	    if (nb[i]>=0) ans[i]=nb[i];
	    else ans[i]=nb[i]+MOD;
	}
	
	int carry=0;
	for (int i=0;i<len+5;i++)
	{
		ans[i]+=carry;
		carry=ans[i]/10;
		ans[i]%=10;
	}
	
	bool mark=false;
	for (int i=len+5;i>=0;i--)
	{
		if (mark) cout<<ans[i];
		if (!mark&&ans[i]!=0)
		{
			mark=true;
			cout<<ans[i];
		}
	}
	return 0;
}
