#include <bits/stdc++.h>
#define MAXN 2100000
#define PI 3.141592654
using namespace std;
class complex_number
{
	public:
		double real;
		double image;
		complex_number(double r=0,double i=0)
		{
			this->real=r;this->image=i;
		}
};
complex_number a[MAXN],b[MAXN],fa[MAXN],fb[MAXN];
int ans[MAXN];

complex_number operator + (const complex_number &x,const complex_number &y)
{
	return complex_number(x.real+y.real,x.image+y.image);
}

complex_number operator - (const complex_number &x,const complex_number &y)
{
	return complex_number(x.real-y.real,x.image-y.image);
}

complex_number operator * (const complex_number &x,const complex_number &y)
{
	return complex_number(x.real*y.real-x.image*y.image,x.real*y.image+x.image*y.real);
}

complex_number unit_root (int k,int n)
{
	return complex_number(cos(2.0*PI*k/n),sin(2.0*PI*k/n));
}

complex_number promote (int n)
{
	return complex_number((double)n,0.0);
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

void DFT (complex_number *a,complex_number *A,int len,int lglen,bool form)
{
	for (int i=0;i<len;i++) A[bit_reverse(i,lglen)]=a[i];
	
	int step=1;
	complex_number w_m,w,temp;
	for (int s=1;s<=lglen;s++)
	{
		step*=2;
		if (form) w_m=unit_root(1,step);
		else w_m=unit_root(-1,step);
		
		for (int k=0;k<len;k+=step)
		{
			w=complex_number(1,0);
			for (int j=0;j<step/2;j++)
			{
				temp=w*A[k+j+step/2];
				A[k+j+step/2]=A[k+j]-temp;
				A[k+j]=A[k+j]+temp;
				w=w*w_m;
			}
		}
	}
	
	if (!form)
		for (int i=0;i<len;i++)
		{
			A[i].real/=len;
			A[i].image/=len;
		}
	
	return;
}

string x,y;
int main ()
{
	cin>>x>>y;
	for (int i=x.length()-1;i>=0;i--)
		a[x.length()-i-1]=promote(x[i]-'0');
	for (int i=y.length()-1;i>=0;i--)
	    b[y.length()-i-1]=promote(y[i]-'0');
	
	int len=1,lglen=0;
	while (len<max(x.length(),y.length())) len*=2,lglen++;
	len*=2,lglen++;
	
	DFT(a,fa,len,lglen,1);
	DFT(b,fb,len,lglen,1);
	
	for (int i=0;i<len;i++) fa[i]=fa[i]*fb[i];
	
	DFT(fa,fb,len,lglen,0);
	
	for (int i=0;i<len;i++) ans[i]=(int)(fb[i].real+0.5);
	
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
