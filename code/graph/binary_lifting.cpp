template<const int LOG_N>
struct BinaryLifting {
  int timer;
  vector<int> tin, tout, h, up[LOG_N];
  vector<vector<int>> adj;
  BinaryLifting(int N) : timer(0), tin(N), tout(N), h(N), adj(N) {
    for(int j = 0; j < LOG_N; ++j) {
      up[j].assign(N, 0);
    }
  }
  void add_edge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  void set_root(int root) {
    dfs(root, root);
  }
  void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for(int i = 0; i + 1 < LOG_N; ++i) {
      up[i + 1][u] = up[i][up[i][u]];
    }
    for(auto v : adj[u]) {
      if(v == p) {
        continue;
      }
      h[v] = h[u] + 1;
      dfs(v, u);
    }
    tout[u] = timer;
  }
  bool is_ancestor(int u, int v) const {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
  int lca(int u, int v) const {
    if(is_ancestor(u, v)) {
      return u;
    }
    if(is_ancestor(v, u)) {
      return v;
    }
    for(int i = LOG_N - 1; i >= 0; --i) {
      if(!is_ancestor(up[i][u], v)) {
        u = up[i][u];
      }
    }
    return up[0][u];
  }
  int dist(int u, int v) const {
    return h[u] + h[v] - 2 * h[lca(u, v)];
  }
  int go_up(int u, int steps) const {
    for(int i = 0; i < LOG_N; ++i) {
      if((steps >> i) & 1) {
        u = up[i][u];
      }
    }
    return u;
  }
};
