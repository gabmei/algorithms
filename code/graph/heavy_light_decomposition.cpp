//IS_EDGE: whether queries are on vertices or edges
//false: vertices, true: edges
template<const bool IS_EDGE>
struct HeavyLightDecomposition {
  vector<int> tin, tout, sz, rin, p, nxt, h;
  vector<vector<int>> adj;
  int t;
  HeavyLightDecomposition(int n) : tin(n), tout(n),
    sz(n), rin(n), p(n), nxt(n), h(n), adj(n) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void set_root(int n) {
    t = 0;
    p[n] = n;
    h[n] = 0;
    prep(n, n);
    nxt[n] = n;
    hld(n,n);
  }
  int get_lca(int u, int v) {
    while(!in_subtree(nxt[u], v)) u = p[nxt[u]];
    while(!in_subtree(nxt[v], u)) v = p[nxt[v]];
    return tin[u] < tin[v] ? u : v;
  }
  bool in_subtree(int u, int v) {
    // is v tin the subtree of u
    return tin[u] <= tin[v] && tin[v] < tout[u];
  }
  template<typename T>
  void get_path_to_ancestor(int u, int anc, T&& get) {
    // returns ranges [l, r) that the path has
    while(nxt[u] != nxt[anc]) {
      get(tin[nxt[u]], tin[u] + 1);
      u = p[nxt[u]];
    }
    // this includes the ancestor!
    // check if range [l,r) is valid when IS_EDGE
    if(tin[anc] + IS_EDGE < tin[u] + 1) {
      get(tin[anc] + IS_EDGE, tin[u] + 1);
    }
  }
  void prep(int u, int par) {
    sz[u] = 1;
    p[u] = par;
    for(int& v : adj[u]) {
      if(v != par) {
        h[v] = 1 + h[u];
        prep(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[adj[u][0]] || adj[u][0] == par) {
          swap(adj[u][0], v);
        }
      }
    }
  }
  void hld(int u, int par) {
    tin[u] = t++;
    rin[tin[u]] = u;
    for(auto v : adj[u]) {
      if(v == par) continue;
      nxt[v] = (v == adj[u][0] ? nxt[u] : v);
      hld(v, u);
    }
    tout[u] = t;
  }
};
