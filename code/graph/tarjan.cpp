vector<int> tarjan(const vector<vector<int>>& adj) {
  int n = (int)adj.size(), timer = 0, ncomps = 0;
  enum State { unvisited, on_stack, visited };
  vector<State> state(n, unvisited);
  vector<int> low(n), tin(n), scc(n), stk;
  auto dfs = [&](auto&& dfs, int u) -> void {
    low[u] = tin[u] = timer++;
    stk.push_back(u);
    state[u] = on_stack;
    for(int v : adj[u]) {
      if(state[v] == unvisited) {
        dfs(dfs, v);
        low[u] = min(low[u], low[v]);
      } else if(state[v] == on_stack) {
        low[u] = min(low[u], tin[v]);
      }
    }
    if(low[u] == tin[u]) {
      int v;
      do {
        v = stk.back();
        stk.pop_back();
        state[v] = visited;
        scc[v] = ncomps;
      } while(v != u);
      ++ncomps;
    }
  };
  for(int u = 0; u < n; ++u) {
    if(state[u] == unvisited) {
      dfs(dfs, u);
    }
  }
  return scc;
}
