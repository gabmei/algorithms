#include<bits/stdc++.h>
using namespace std;

template<class T>
struct RMQ{
	int N;
	int K=25;
	vector<vector<T>>st;
	RMQ(){};
	RMQ(const vector<T>& V){
		N=V.size();
		st=vector<vector<T>>(K+1,vector<T>(N));
		for(int i=0;i<N;i++){
			st[0][i]=V[i];
		}
		for(int j=1;j<=K;j++){
			for(int i=0;i+(1<<j)<=N;i++){
				st[j][i]=min(st[j-1][i],st[j-1][i+(1<< (j-1) )]);
			}
		}
	}
	T query(int l, int r){
		int j = 31-__builtin_clz(r-l+1);
		return min(st[j][l],st[j][r-(1<<j)+1]);
	}
};

struct LCA{
	vector<int>depth,epath,ret,time;
	RMQ<int> rmq;

	int n;
	LCA(vector<vector<int>>& adj,int root=0){
		n=adj.size();
		depth.resize(n);
		time.resize(n);
		dfs(adj,root);
		rmq=RMQ<int>(ret);
	}
	void dfs(vector<vector<int>>& adj, int u=0, int p=-1, int h=0){
		depth[u]=h;
		time[u]=epath.size();
        	epath.push_back(u);
		ret.push_back(time[u]);
		for(int v:adj[u]){
			if (v!=p){
				dfs(adj, v,u, h + 1);
				epath.push_back(u);
				ret.push_back(time[u]);
			}
		}
	}	
	int lca(int a, int b){
		tie(a,b)=minmax(time[a],time[b]);
		return epath[rmq.query(a,b)];
	}

	int dist(int a, int b){
		return depth[a]+depth[b]-2*depth[lca(a,b)];
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	for(int c=1;c<=t;c++){
		int n;
		cin>>n;
		vector<vector<int>>adj(n);

		for(int i=0;i<n;i++){
			int m;cin>>m;
			while(m--){
				int j;cin>>j;
				j--;
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
		LCA foo(adj);
		cout<<"Case "<<c<<":\n";
		int q;cin>>q;
		while(q--){
			int l,r;
			cin>>l>>r;
			l--;r--;
			cout<<foo.lca(l,r)+1<<'\n';
		}
	}
	
	return 0;
}
