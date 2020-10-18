#include<bits/stdc++.h>
using namespace std;

vector<int>p,sz;
void init_(int n){
	p=vector<int>(n+1);
	iota(p.begin(),p.end(),0);

	sz=vector<int>(n+1,1);
}
int get_set(int a){
	return p[a]=(p[a]==a?a:get_set(p[a]));//path compression
}

void union_set(int a, int b){
	a=get_set(a);
	b=get_set(b);

	if(a!=b){
		//Union by size
		if(sz[a]>sz[b]){
			swap(a,b);
		}
		p[a]=b;
		sz[b]+=sz[a];

	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin>>n>>m;
	init_(n);

	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		union_set(u,v);
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=get_set(i)==i;
	}
	cout<<cnt-1<<'\n';
	
	return 0;
}