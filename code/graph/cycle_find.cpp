vector<int> get_cycle(const vector<vector<int>>& adj) {
  enum State { unvisited, on_stack, visited };
  int n = (int)adj.size();
  vector<State> vis(n, unvisited);
  vector<int> par(n, -1);
  int st = -1, ft = -1;
  auto dfs = [&](auto&& dfs, int u, int p) -> bool {
    vis[u] = on_stack;
    for(auto v : adj[u]) {
      if(v == p) {
        continue;
      }
      if(vis[v] == unvisited) {
        par[v] = u;
        if(dfs(dfs, v, u)) {
          return true;
        }
      } else if(vis[v] == on_stack) {
        st = v;
        ft = u;
        return true;
      }
    }
    vis[u] = visited;
    return false;
  };
  bool has_cycle = false;
  for(int u = 0; u < n; ++u) {
    if(vis[u] == unvisited && dfs(dfs, u, u)) {
      has_cycle = true;
      break;
    } 
  }
  if(!has_cycle) {
    return {};
  }
  vector<int> cycle;
  for(int u = ft; u != st; u = par[u]) {
    cycle.emplace_back(u);
  }
  cycle.emplace_back(st);
  reverse(begin(cycle), end(cycle));
  return cycle;
}
