#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LCA{
 	vector<int> height, epath, tin, segtree;
    int n;
	int m;
    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        tin.resize(n);
        dfs(adj, root);
        m = epath.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int u,int p=-1, int h=0) {
        height[u] = h;
        tin[u]=epath.size();
        epath.push_back(u);
        for (int v:adj[u]) {
            if (v!=p) {
                dfs(adj, v,u, h + 1);
                epath.push_back(u);
            }
        }
    }

    void build(int pos, int l, int r) {
        if (l==r) {
            segtree[pos] = epath[l];
        } else {
            int mid = (l+r)/2;
            build(2*pos, l, mid);
            build(2*pos+1, mid + 1, r);
            int left = segtree[2*pos], right = segtree[2*pos+1];
            segtree[pos] = (height[left] < height[right]) ? left : right;
        }
    }

    int query(int pos, int l, int r, int a, int b) {
        if (l > b || r < a)return -1;
        if (l >= a && r <= b)return segtree[pos];
        int mid = (l+r)/2;
        int left = query(pos << 1, l, mid, a, b);
        int right = query(pos << 1 | 1, mid + 1, r, a, b);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
		tie(u,v)=minmax(tin[u],tin[v]);
        return query(1, 0, m-1, u,v);
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