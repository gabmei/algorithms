#include<bits/stdc++.h>
using namespace std;

struct LCA{
    int n,l,timer;
    vector<int>tin,tout,depth;
    vector<vector<int>>up;
    LCA(const vector<vector<int>>& adj, int root=0):n((int)adj.size()),tin(n),tout(n),depth(n){
        l=31-__builtin_clz(n);
        timer=0;
        up=vector<vector<int>>(l+1,vector<int>(n));
        dfs(root,root,0,adj);
    }
    void dfs(int u, int p, int h, const vector<vector<int>>& adj){
        tin[u]=timer++;
        depth[u]=h;
        up[0][u]=p;
        for(int i=1;i<=l;i++){
            up[i][u]=up[i-1][up[i-1][u]];
        }
        for(int v:adj[u]){
            if(v!=p)dfs(v,u,h+1,adj);
        }
        tout[u]=timer++;
    }
    int goUp(int u, int steps){
        for(int i=0;i<=l;i++){
            if(steps & (1<<i))u=up[i][u];
        }
        return u;
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
