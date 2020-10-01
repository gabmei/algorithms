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


int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int source=0;
		int N;scanf("%d",&N);
		double D;scanf("%lf",&D);

		vector<vector<int>>dots;
		ll total=0;
		Dinic kinho(2*(N+1));
		for(int i=0;i<N;i++){
			int x, y, n, m;
			scanf("%d%d%d%d",&x,&y,&n,&m);
			dots.push_back({x,y,n,m});
			total+=n;
			kinho.Add_Edge(i+1,N+i+1,(ll)dots[i][3]);
			kinho.Add_Edge(source,i+1,(ll)dots[i][2]);
		}
		
	
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				double dist = 0;
				dist+=(dots[i][0]-dots[j][0])*((dots[i][0]-dots[j][0]));
				dist+=(dots[i][1]-dots[j][1])*((dots[i][1]-dots[j][1]));

				if(dist<=D*D){

					kinho.Add_Edge(N+i+1,j+1,(ll)INF);
					kinho.Add_Edge(N+j+1,i+1,(ll)INF);

				}
			}
		}
		vector<int> ans;

		for(int sink=0;sink<N;sink++){
			ll mf=kinho.MaxFlow(source,sink+1);
			
			if(mf==total){
				ans.push_back(sink);
			}
			for(Edge &e:kinho.edges){
				e.flow=0;
			}
		}

		if(ans.empty()){
			printf("-1\n");
		}else{
			for(int i=0;i<ans.size()-1;i++){
				printf("%d ",ans[i]);
			}
			printf("%d\n",ans.back());
		}

	}
	
	return 0;
}