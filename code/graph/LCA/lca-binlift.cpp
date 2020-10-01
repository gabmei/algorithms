#include<bits/stdc++.h>
using namespace std;
int n, l, timer;
vector<vector<int>>adj,up;
vector<int>tin,tout,depth;

void dfs(int u, int p, int h=0){
	tin[u]=timer++;
	depth[u]=h;
	up[u][0]=p;
	for(int i=1;i<=l;i++){
		up[u][i]=up[up[u][i-1]][i-1];
	}
	for(int v:adj[u]){
		if(v!=p){
			dfs(v,u,h+1);
		}
	}
	tout[u]=timer++;
}
int go_up(int u, int steps){
	for(int i=0;i<=l;i++){
		if(steps & (1<<i))u=up[u][i];
	}
	return u;
}
bool is_ancestor(int u, int v){
	return tin[u]<=tin[v] && tout[u]>=tout[v];
}
int lca(int a, int b){
	
	if(is_ancestor(a,b))return a;
	if(is_ancestor(b,a))return b;

	for(int i=l;i>=0;i--){
		if(!is_ancestor(up[a][i],b)){
			a=up[a][i];
		}
	}
	return up[a][0];
}
int dist(int a, int b){
	return depth[a]+depth[b]-2*depth[lca(a,b)];
}
void preprocess(int root){
	tin.resize(n);
	tout.resize(n);
	depth.resize(n);
	timer=0;
	l=31-__builtin_clz(n);
	up=vector<vector<int>>(n,vector<int>(l+1));
	dfs(root,root);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	for(int c=1;c<=t;c++){
		cin>>n;
		adj=vector<vector<int>>(n);

		for(int i=0;i<n;i++){
			int m;cin>>m;
			while(m--){
				int j;cin>>j;
				j--;
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
		preprocess(0);
		cout<<"Case "<<c<<":\n";
		int q;cin>>q;
		while(q--){
			int l,r;
			cin>>l>>r;
			l--;r--;
			cout<<lca(l,r)+1<<'\n';
		}
	}
	
	return 0;
}