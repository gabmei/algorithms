#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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
	//returns where the vertex u is in the min-cut (S,T) 
	//false: u in S, true: u in T
	bool cut(int u){return dist[u]==n+1;}
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n,m,s,v;
	while(cin>>n>>m>>s>>v){
		vector<pair<double,double> > Esses,Tes;
		Dinic kinho(n+2*m+2);
		for(int i=0;i<n;i++){
			double x,y;
			cin>>x>>y;
			Esses.push_back({x,y});

			kinho.Add_Edge(0,i+1,1);
		}
		for(int i=0;i<m;i++){
			double x,y;
			cin>>x>>y;
			Tes.push_back({x,y});
			
			kinho.Add_Edge(n+1+2*i,n+1+2*i+1,1);
			kinho.Add_Edge(n+1+2*i+1,n+1+2*m,1);
		}

		double dmax=v*v*s*s;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				double dx,dy;
				dx=Esses[i].first-Tes[j].first;
				dy=Esses[i].second-Tes[j].second;
				double dist = dx*dx + dy*dy;
				
				if(dist <=dmax){
					kinho.Add_Edge(i+1,n+1+2*j,1);
				}
			}
		}
		
		ll mf = kinho.MaxFlow(0,n+1+2*m);

		cout<<n-mf<<'\n';
	}
	return 0;
}