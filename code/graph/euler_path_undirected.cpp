vector<pair<int, int>> adj[MAXN];
int deg[MAXN]; bool seen_edges[MAXM];
vector<int> path, path_edges;
void calc_deg(int n) {
  for(int u = 0; u < n; ++u) {
    for(auto [v, id] : adj[u]) {
      deg[v]++;
    }
  }
}
bool has_eulerian_path(int n) {
  int odd_cnt = 0;
  for(int u = 0; u < n; ++u) {
    if(deg[u] % 2) odd_cnt++;
  }
  return odd_cnt == 0 // eulerian circuit
      || odd_cnt == 2; // eulerian path
}
void dfs(int u, int from_id) {
  while(!adj[u].empty()) {
    auto [v, id] = adj[u].back();
    adj[u].pop_back();
    if(seen_edges[id]) continue;
    seen_edges[id] = true;
    dfs(v, id);
  }
  path.emplace_back(u);
  if(from_id != -1) path_edges.emplace_back(from_id);
}
int get_start_node(int n) {
  int st = 0;
  for(int u = 0; u < n; ++u) {
    if(deg[u] % 2) return u;
    if(deg[u] > 0) st = u;
  }
  return st;
}
bool get_eulerian_path(int n, int m) {
  calc_deg(n);
  if(!has_eulerian_path(n)) return false;
  dfs(get_start_node(n), -1);
  return (int)path_edges.size() == m;
}
// remember to reverse path_edges!
