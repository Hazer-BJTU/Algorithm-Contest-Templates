#include <bits/stdc++.h>
#define MAXN 200005
#define SET_LENGTH 26
using namespace std;
struct Trie {
	char key;
	int cnt,vis;
	int p[SET_LENGTH];
	int fail;
	static int top,deg[MAXN];
	static Trie nodes[MAXN];
	Trie() {
		key='\0';
		cnt=vis=0;
		for (int i=0;i<SET_LENGTH;i++)
			p[i]=0;
		fail=0;
	}
	static int make_node(char new_key) {
		top++;
		nodes[top].key=new_key;
		return top;
	}
	void insert(string &str,int pos,int index) {
		if (pos==str.length()) {
			cnt=index;
			return;
		}
		int dest=str[pos]-'a';
		if (!p[dest]) p[dest]=make_node(str[pos]);
		nodes[p[dest]].insert(str,pos+1,index);
		return;
	}
	static void build(int root) {
		nodes[root].fail=root,deg[root]++;
		queue<int>que;
		int next_node;
		for (int i=0;i<SET_LENGTH;i++) {
			next_node=nodes[root].p[i];
			if (next_node) {
				nodes[next_node].fail=root,deg[root]++;
				que.push(next_node);
			}
		}
		while(!que.empty()) {
			int now=que.front();que.pop();
			for (int i=0;i<SET_LENGTH;i++) {
				next_node=nodes[now].p[i];
				if (next_node) {
					int pos=nodes[now].fail;
					while(!nodes[pos].p[i]&&pos!=root) pos=nodes[pos].fail;
					if (nodes[pos].p[i]) nodes[next_node].fail=nodes[pos].p[i],deg[nodes[pos].p[i]]++;
					else nodes[next_node].fail=root,deg[root]++;
					que.push(next_node);
				}
			}
		}
		return;
	}
	static void query(string &str,int root) {
		int now=root;
		for (int i=0;i<str.length();i++) {
			int dest=str[i]-'a';
			if (nodes[now].p[dest]) now=nodes[now].p[dest];
			else {
				while(!nodes[now].p[dest]&&now!=root) now=nodes[now].fail;
				if (nodes[now].p[dest]) now=nodes[now].p[dest];
				else continue;
			}
			nodes[now].vis++;
		}
		return;
	}
	static void topology(int *ans) {
		queue<int>que;
		for (int i=1;i<=top;i++)
			if (!deg[i]) que.push(i);
		while(!que.empty()) {
			int now=que.front();que.pop();
			ans[nodes[now].cnt]+=nodes[now].vis;
			nodes[nodes[now].fail].vis+=nodes[now].vis;
			nodes[now].vis=0;
			deg[nodes[now].fail]--;
			if (!deg[nodes[now].fail])
				que.push(nodes[now].fail);
		}
		return;
	}
};
int Trie::top=0,Trie::deg[MAXN];
Trie Trie::nodes[MAXN];
int n,ans[MAXN],num[MAXN],top;
string s,t;
map<string,int>hash_list;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int root=Trie::make_node('0');
	for (int i=1;i<=n;i++) {
		cin>>s;
		map<string,int>::iterator it=hash_list.find(s);
		if (it==hash_list.end()) {
			hash_list.insert(pair<string,int>(s,++top));
			Trie::nodes[root].insert(s,0,top);
			num[i]=top;
		} else num[i]=it->second;
	}
	Trie::build(root);
	cin>>t;
	Trie::query(t,root);
	Trie::topology(ans);
	for (int i=1;i<=n;i++)
		cout<<ans[num[i]]<<'\n';
	return 0;
} 
