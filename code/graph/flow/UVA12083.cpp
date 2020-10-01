#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9;
struct Edge{
	int u,v;
	ll cap,flow;
	Edge(int u,int v, ll cap):u(u),v(v),cap(cap),flow(0ll){}
};

struct Dinic{
	const ll flow_inf=1e18;
	vector<Edge>edges;
	vector<vector<int>>adj;
	int n;
	vector<int>dist,ptr;

	Dinic(int n):n(n){
		adj.resize(n);
		dist.resize(n);
		ptr.resize(n);
	}
	void Add_Edge(int u, int v, ll cap){
		if(u!=v) {
			edges.emplace_back(u,v,cap);
			adj[u].emplace_back(edges.size()-1);
			edges.emplace_back(v,u,0);
			adj[v].emplace_back(edges.size()-1);
		}		
	}
	bool bfs(int s, int t){
		fill(dist.begin(),dist.end(),n+1);

		dist[s]=0;
		queue<int>q;q.push(s);

		while(!q.empty()){
			int u = q.front();q.pop();
			if(u==t)break;

			for(int id:adj[u]){
				Edge &e = edges[id];
				if(e.flow<e.cap && dist[e.v]>dist[e.u]+1){
					dist[e.v]=dist[e.u]+1;
					q.emplace(e.v);
				}
			}
		}

		return dist[t]!=n+1;
	}

	ll dfs(int u, int t,ll flow){
		if(u==t||flow==0){
			return flow;
		}

		for(int &i=ptr[u];i<adj[u].size();i++){
			Edge &e=edges[adj[u][i]];
			Edge &oe=edges[adj[u][i]^1];

			if(dist[e.v]==dist[e.u]+1){
				ll amt=e.cap-e.flow;
				amt=min(flow,amt);

				if(ll ret=dfs(e.v,t,amt)){
					e.flow+=ret;
					oe.flow-=ret;
					return ret;
				}
			}
		}
		return 0ll;
	}

	ll MaxFlow(int s, int t){
		ll total=0;
		while(bfs(s,t)){
			fill(ptr.begin(),ptr.end(),0);
			while(ll flow=dfs(s,t,flow_inf)){
				total+=flow;
			}
		}

		return total;
	}
};
vector<vector<int>>adj;
vector<int>color; 
void painting_dfs(int u,int p=0){
	color[u]=p;

	for(int v:adj[u]){
		if(color[v]==-1){
			painting_dfs(v,1-p);
		}
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;cin>>T;
	while(T--){
		int n;cin>>n;
		vector<int>height(n);
		vector<char>gender(n);
		vector<string>music(n);
		vector<string>sport(n);

		for(int i=0;i<n;i++){
			cin>>height[i]>>gender[i]>>music[i]>>sport[i];
		}
		Dinic kinho(n+2);
		color=vector<int>(n,-1);
		adj=vector<vector<int>>(n);

		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				bool f0,f1,f2,f3;
				f0=(abs(height[i]-height[j])>40);
				f1=(gender[i]==gender[j]);
				f2=(music[i]!=music[j]);
				f3=(sport[i]==sport[j]);

				if(!f0 && !f1 && !f2 && !f3){
					//cout<<i+1<<' '<<j+1<<'\n';
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}
		for(int i=0;i<n;i++){
			if(color[i]==-1){
				painting_dfs(i);
			}
			if(color[i]==0){
				kinho.Add_Edge(0,i+1,1);
			}else{
				kinho.Add_Edge(i+1,n+1,1);
			}
			for(int j:adj[i]){
				if(color[i]==0 && color[j]==1){
					//cout<<i+1<<' '<<j+1<<'\n';
					kinho.Add_Edge(i+1,j+1,1);
					
				}
			}
		}

			
		cout<<n-kinho.MaxFlow(0,n+1)<<'\n';
	}
	
	return 0;
}