template<class T>
struct Dinic{
    struct Edge{
        int u,v;
        T cap,flow;
        Edge(int _u,int _v, T _cap):u(_u),v(_v),cap(_cap),flow(0){}
    };
    int m = 0, n;
    vector<Edge>edges;
    vector<vector<int>>adj;
    vector<int>dist,ptr;
    Dinic(int _n):n(_n),adj(n),dist(n),ptr(n){}
    void addEdge(int u, int v, T cap){
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

    T dfs(int u, int t, T flow){
        if(u==t||flow==0){
            return flow;
        }
        for(int &i=ptr[u];i<(int)adj[u].size();++i){
            Edge &e=edges[adj[u][i]];
            Edge &oe=edges[adj[u][i]^1];

            if(dist[e.v]==dist[e.u]+1){
                T amt=e.cap-e.flow;
                amt=min(flow,amt);
                if(T ret=dfs(e.v,t,amt)){
                    e.flow+=ret;
                    oe.flow-=ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    T maxFlow(int s, int t){
        T total=0;
        while(bfs(s,t)){
            fill(begin(ptr),end(ptr),0);
            while(T flow=dfs(s,t,numeric_limits<T>::max())){
                total+=flow;
            }
        }
        return total;
    }
    //returns where in the min-cut (S,T) the vertex u is
    //false: u in S, true: u in T
    bool cut(int u){return dist[u]==n+1;}
};
