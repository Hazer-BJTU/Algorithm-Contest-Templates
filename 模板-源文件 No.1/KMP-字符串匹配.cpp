#include <bits/stdc++.h>
#define MAXN 1000005
#define ENDS '$'
using namespace std;
string s1,s2;
int helper[MAXN],ans[MAXN];

void KMP (string P,string T,int *border,int *dest,bool type)
{
	int m=P.length(),n=T.length();
	P=' '+P+ENDS;T=' '+T;
	if (type) dest[1]=0;
	
	int i=0;
	for (int j=type+1;j<=n;j++)
	{
		while (i>0&&P[i+1]!=T[j]) i=border[i];
		if (P[i+1]==T[j]) i++;
		dest[j]=i;
	}
}

int main ()
{
	cin>>s1>>s2;
	
	KMP(s2,s2,helper,helper,1);
	KMP(s2,s1,helper,ans,0);
	
	for (int i=1;i<=s1.length();i++) if (ans[i]==s2.length()) cout<<i-s2.length()+1<<'\n';
	for (int i=1;i<=s2.length();i++) cout<<helper[i]<<' ';
	return 0;
}
