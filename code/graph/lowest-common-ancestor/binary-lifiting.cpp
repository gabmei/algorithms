template<const int l = 20>
struct LCA{
    int n,timer;
    vector<int>tin,tout,depth;
    array<vector<int>,l + 1>up,magic;
    LCA(const vector<vector<pair<int,int>>>& adj, int root=0):n((int)adj.size()),tin(n),tout(n),depth(n){
        timer=0;
        for(int i=0;i<=l;++i){
            up[i] = magic[i] = vector<int>(n);
        }
        dfs(root,root,0,0,adj);
    }
    void dfs(int u, int p, int w,int h, const vector<vector<pair<int,int>>>& adj){
        tin[u]=timer++;
        depth[u]=h;
        up[0][u]=p;
        magic[0][u] = w;
        for(int i=1;i<=l;i++){
            up[i][u]=up[i-1][up[i-1][u]];
            magic[i][u] = max(magic[i-1][u],magic[i-1][up[i-1][u]]);
        }
        for(auto [v,w] :adj[u]){
            if(v!=p)dfs(v,u,w,h+1,adj);
        }
        tout[u]=timer++;
    }
    int goUp(int u, int steps){
        for(int i=0;i<=l;i++){
            if(steps & (1<<i))u=up[i][u];
        }
        return u;
    }
    int getPathToAncestor(int u, int anc){
        int ans = 0;
        for(int i=l;i>=0;--i){
            if(depth[up[i][u]] > depth[anc]){
                ans = max(ans, magic[i][u]);
                u = up[i][u];
            }
        }
        if(u != anc)ans = max(ans, magic[0][u]);
        return ans;
    }
    bool isAncestor(int u, int v){
        return tin[u]<=tin[v] && tout[u]>=tout[v];
    }
    int lca(int a, int b){
        if(isAncestor(a,b))return a;
        if(isAncestor(b,a))return b;

        for(int i=l;i>=0;i--){
            if(!isAncestor(up[i][a],b)){
                a=up[i][a];
            }
        }
        return up[0][a];
    }
    int dist(int a, int b){
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
};
