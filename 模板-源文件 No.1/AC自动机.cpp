#include <bits/stdc++.h>
#define MAXN 1000005
#define SET_LENGTH 26
using namespace std;
struct Trie {
	char key;
	int cnt;
	Trie *p[SET_LENGTH];
	Trie *fail;
	Trie(char new_key) {
		cnt=0;
		key=new_key;
		for (int i=0;i<SET_LENGTH;i++)
			p[i]=NULL;
		fail=NULL;
	}
	void insert(string &str,int pos) {
		if (pos==str.length()) {
			cnt++;
			return;
		}
		int dest=str[pos]-'a';
		if (!p[dest]) p[dest]=new Trie(str[pos]);
		p[dest]->insert(str,pos+1);
		return;
	}
}root('0');
void buildAC(Trie *root) {
	root->fail=root;
	queue<Trie*>que;
	for (int i=0;i<SET_LENGTH;i++) {
		if (root->p[i]) {
			root->p[i]->fail=root;
			que.push(root->p[i]);
		}
	}
	while(!que.empty()) {
		Trie *now=que.front();que.pop();
		for (int i=0;i<SET_LENGTH;i++) {
			if (now->p[i]) {
				Trie *pos=now->fail;
				while(!pos->p[i]&&pos!=root) pos=pos->fail;
				if (pos->p[i]) now->p[i]->fail=pos->p[i];
				else now->p[i]->fail=root;
				que.push(now->p[i]);
			}
		}
	}
	return;
}
void query(string &str,Trie *root,int &ans) {
	Trie *now=root;
	for (int i=0;i<str.length();i++) {
		int dest=str[i]-'a';
		if (now->p[dest]) now=now->p[dest];
		else {
			while(!now->p[dest]&&now!=root) now=now->fail;
			if (now->p[dest]) now=now->p[dest];
			else continue;
		}
		for (Trie *temp=now;temp->cnt;temp=temp->fail) {
			ans+=temp->cnt;
			temp->cnt=0;
		}
	}
	return;
}
int n,ans;
string s;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>s;
		root.insert(s,0);
	}
	buildAC(&root);
	cin>>s;
	query(s,&root,ans);
	cout<<ans;
	return 0;
}
