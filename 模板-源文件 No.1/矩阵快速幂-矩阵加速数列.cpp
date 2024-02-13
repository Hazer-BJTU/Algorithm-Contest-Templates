#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 105
using namespace std;
void matrixPrint(long long (*C)[MAXN],int n) {
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++)
			cout<<C[i][j]<<' ';
		cout<<'\n';
	}
	return;
}
void setE(long long (*C)[MAXN],int n) {
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (i==j) C[i][j]=1;
				else C[i][j]=0;
}
void setZero(long long (*C)[MAXN],int n) {
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			C[i][j]=0;
}
void matrixMulti(long long (*C)[MAXN],long long (*A)[MAXN],int n) {
	long long temp[MAXN][MAXN];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) {
			long long sum=0;
			for (int k=1;k<=n;k++)
				sum=(sum+C[i][k]*A[k][j])%MOD;
			temp[i][j]=sum;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			C[i][j]=temp[i][j];
	return;
}
void matrixPlus(long long (*C)[MAXN],long long (*A)[MAXN],int n) {
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			C[i][j]=(C[i][j]+A[i][j])%MOD;
	return;
}
void quick_power(long long (*A)[MAXN],int p,int n,long long (*C)[MAXN]) {
	int top=0;
	bool instruction[MAXN];
	while (p!=0) {
		instruction[++top]=p%2;
		if (instruction[top]) p--;
		else p/=2;
	}
	setE(C,n);
	for (int i=top;i>=1;i--) {
		if (instruction[i]) matrixMulti(C,A,n);
		else matrixMulti(C,C,n);
	}
}

int n;
long long A[MAXN][MAXN],C[MAXN][MAXN];
int main() {
	A[1][1]=1,A[1][2]=0,A[1][3]=1;
	A[2][1]=1,A[2][2]=0,A[2][3]=0;
	A[3][1]=0,A[3][2]=1,A[3][3]=0;
	
	int T;
	cin>>T;
	while (T--) {
		cin>>n;
		if (n<=3) cout<<"1\n";
		else {
			quick_power(A,n-3,3,C);
			long long ans=(C[1][1]+C[1][2]+C[1][3])%MOD;
			cout<<ans<<'\n';
		}
	}
	return 0;
}
