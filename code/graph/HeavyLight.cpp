vector<vector<int>> adj;
struct HeavyLight{
	vector<int>pos,pai,h,sz;
	//vector<int> v; //vetor para buildar a segtree
	SegmentTree tree;
	int timer;
	
	HeavyLight(int n, int root=0):pos(n),pai(n),h(n),sz(n),tree(n){	
		dfs(root);
		timer = 0;
		h[root]=root;
		buildHLD(root);
		//tree.build(v);
	}
	void dfs(int u, int p=-1){
		sz[u] = 1;
		for(int &v:adj[u]){
			if(v!=p){
				dfs(v,u);
				sz[u]+=sz[v];
				if(sz[v] > sz[adj[u][0]] || adj[u][0] == p)swap(v,adj[u][0]);
			}
		}
	}
	void buildHLD(int u, int p=-1){
		pos[u]=timer++;
		//v[pos[u]]=val[u]; // valor presente no nó u
		for(int v:adj[u]){
			if(v!=p){
				pai[v]=u;
				h[v] =(v==adj[u][0] ? h[u] : v);
				buildHLD(v,u);
			}
		}
	}
	node queryPath(int a ,int b){
		if(pos[a]<pos[b])swap(a,b);
 
		if(h[a]==h[b])return tree.query(pos[b],pos[a]);
 
		return tree.query(pos[h[a]],pos[a]) + queryPath(pai[h[a]],b);
	}
	void updatePath(int a, int b, node x){	
		if(pos[a]<pos[b])swap(a,b);
 
		if(h[a]==h[b]){
			tree.update(pos[b],pos[a],x);
			return;
		}
		tree.update(pos[h[a]],pos[a],x);
		updatePath(pai[h[a]],b,x);
	}
};
