struct TwoEdgeComponent {
  enum State { unvisited, on_stack, visited };
  int n, timer, nedge;
  vector<vector<pair<int, int>>> adj;
  vector<State> state;
  vector<int> tin, low, edge_stk;
  vector<bool> used_edge;
  vector<vector<int>> two_edge_component;
  vector<pair<int, int>> bridge;
  TwoEdgeComponent(int n) : n(n), timer(0),
  nedge(0), adj(n), state(n, unvisited),
  tin(n), low(n) {}
  void add_edge(int a, int b) {
    adj[a].emplace_back(b, nedge);
    adj[b].emplace_back(a, nedge);
    nedge += 1;
  }
  void dfs(int u, int edge_id) {
    low[u] = tin[u] = timer++;
    edge_stk.emplace_back(u);
    state[u] = on_stack;
    for(auto [v, id] : adj[u]) {
      if(edge_id == id) {
        continue;
      }
      if(state[v] == unvisited) {
        used_edge[id] = true;
        dfs(v, id);
        low[u] = min(low[u], low[v]);
        if(low[v] > tin[u]) {
          bridge.emplace_back(u, v);
        }
      } else if(state[v] == on_stack) {
        low[u] = min(low[u], tin[v]);
      }
    }
    if(low[u] == tin[u]) {
      two_edge_component.emplace_back();
      auto& comp = two_edge_component.back();
      do {
        comp.emplace_back(edge_stk.back());
        edge_stk.pop_back();
        state[comp.back()] = visited;
      } while(comp.back() != u);
    }
  }
  void tarjan() {
    used_edge.assign(nedge, false);
    for(int u = 0; u < n; ++u) {
      if(state[u] == unvisited) {
        dfs(u, -1);
      }
    }
  }
  pair<vector<vector<int>>, vector<int>> build_bridge_tree() const {
    int sz = (int)two_edge_component.size();
    vector<vector<int>> g(sz);
    vector<int> bcc(n);
    for(int id = 0; id < sz; ++id) {
      for(auto node : two_edge_component[id]) {
        bcc[node] = id;
      }
    }
    for(int u = 0; u < n; ++u) {
      for(auto [v, _] : adj[u]) {
        if(bcc[u] != bcc[v]) {
          g[bcc[u]].emplace_back(bcc[v]);
          g[bcc[v]].emplace_back(bcc[u]);
        }
      }
    }
    return {g, bcc};
  }
};
