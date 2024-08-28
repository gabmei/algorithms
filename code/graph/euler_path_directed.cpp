vector<pair<int, int>> adj[MAXN];
int ind[MAXN], outd[MAXN];
vector<int> path, path_edges;
void calc_deg(int n) {
  for(int u = 0; u < n; ++u) {
    for(auto [v, id] : adj[u]) {
      ind[v]++;
      outd[u]++;
    }
  }
}
bool has_eulerian_path(int n) {
  int st_cnt = 0, ft_cnt = 0;
  for(int u = 0; u < n; ++u) {
    if(abs(ind[u] - outd[u]) > 1) return false;
    if(outd[u] - ind[u] == +1) st_cnt++;
    if(outd[u] - ind[u] == -1) ft_cnt++;
  }
  return (st_cnt == 0 && ft_cnt == 0) // eulerian circuit
      || (st_cnt == 1 && ft_cnt == 1); // eulerian path
}
void dfs(int u, int from_id) {
  while(!adj[u].empty()) {
    auto [v, id] = adj[u].back();
    adj[u].pop_back();
    dfs(v, id);
  }
  path.emplace_back(u);
  if(from_id != -1) path_edges.emplace_back(from_id);
}
int get_start_node(int n) {
  int st = 0;
  for(int u = 0; u < n; ++u) {
    if(outd[u] - ind[u] == +1) return u;
    if(outd[u] > 0) st = u;
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
