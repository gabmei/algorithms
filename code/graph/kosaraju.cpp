vector<int> kosaraju(const vector<vector<int>>& adj) {
  int n = (int)adj.size();
  vector<vector<int>> radj(n);
  for(int u = 0; u < n; ++u) {
    for(auto v : adj[u]) radj[v].emplace_back(u);
  }
  vector<int> ord;
  vector<bool> vis(n);
  auto dfs = [&](auto&& dfs, int u) -> void {
    vis[u] = true;
    for(auto v : adj[u]) {
      if(!vis[v]) dfs(dfs, v);
    }
    ord.emplace_back(u);
  };
  for(int u = 0; u < n; ++u) {
    if(!vis[u]) dfs(dfs, u);
  }
  vector<int> scc(n, -1);
  int comp = 0;
  auto dfs2 = [&](auto&& dfs2, int u) -> void {
    scc[u] = comp;
    for(auto v : radj[u]) {
      if(scc[v] == -1) dfs2(dfs2, v);
    }
  };
  reverse(begin(ord), end(ord));
  for(int u : ord) {
    if(scc[u] == -1) {
      dfs2(dfs2, u);
      comp += 1;
    }
  }
  return scc;
}
