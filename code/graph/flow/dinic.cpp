#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e15;
struct Edge{
	int u,v;
	ll cap,flow;
	Edge(int _u,int _v, ll cap):u(_u),v(_v),cap(cap),flow(0ll){}
};

struct Dinic{
	const ll flow_inf=1e18;
    int m = 0, n;
	vector<Edge>edges;
	vector<vector<int>>adj;
	vector<int>dist,ptr;

	Dinic(int _n):n(_n),adj(n),dist(n),ptr(n){}

	void addEdge(int u, int v, ll cap){
		if(u!=v) {
			edges.emplace_back(u,v,cap);
			edges.emplace_back(v,u,0);
            adj[u].emplace_back(m++);
			adj[v].emplace_back(m++);
		}		
	}
	bool bfs(int s, int t){
		fill(begin(dist),end(dist),n+1);

		dist[s]=0;
		queue<int>q({s});

		while(!q.empty()){
			int u = q.front();
            q.pop();
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

		for(int &i=ptr[u];i<(int)adj[u].size();i++){
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

	ll maxFlow(int s, int t){
		ll total=0;
		while(bfs(s,t)){
			fill(begin(ptr),end(ptr),0);
			while(ll flow=dfs(s,t,flow_inf)){
				total+=flow;
			}
		}

		return total;
	}
	//returns where in the min-cut (S,T) the vertex u is
	//false: u in S, true: u in T
	bool cut(int u){return dist[u]==n+1;}
};
const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,r,c;
    cin>>n>>m>>r>>c;
    vector<vector<ll>>g(n+2,vector<ll>(m+2));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>g[i][j];
        }
    }
    g[r][c] = inf;
    auto get_id = [&](int x, int y){
        return 2 * (x * (m + 2) + y);
    };
    
    Dinic kinho(2*(n+2)*(m+2));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int id = get_id(i,j);
            kinho.addEdge(id,id^1,g[i][j]);
            for(int d=0;d<4;++d){
                int ni = i + dx[d];
                int nj = j + dy[d];
                kinho.addEdge(id^1,get_id(ni,nj),inf);
            }
        }
    }
    int source = get_id(r,c);
    int sink = get_id(n+1,m+1);
    for(int i=1;i<=n;++i){
        kinho.addEdge(get_id(i,0),sink,inf);
        kinho.addEdge(get_id(i,m+1),sink,inf);
    }
    for(int i=1;i<=m;++i){
        kinho.addEdge(get_id(0,i),sink,inf);
        kinho.addEdge(get_id(n+1,i),sink,inf);
    }

    ll ans = kinho.maxFlow(source,sink);
    cout<<ans<<'\n';
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int id = get_id(i,j);
            cout<<(kinho.cut(id) != kinho.cut(id^1)? 'X' : '.');
        }
        cout<<'\n';
    }

    
    return 0;
}
