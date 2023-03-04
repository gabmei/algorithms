void usedp(int u, LineContainer& dp) {
  ans[u] = min(ans[u], S[u] + dist[u] * V[u] - dp.query(V[u])); 
}
void filllight(int u, int p, LineContainer& dp) {
  usedp(u, dp);
  for(auto [v, _] : adj[u]) {
    if(v == p) continue;
    filllight(v, u, dp);
  }
}
void dfs(int u, int p, LineContainer& dp) {
  dp.add(dist[u], -ans[u]);
  int big = -1;
  for(auto [v, w] : adj[u]) {
    if(v == p) continue;
    if(big == -1 || sz[v] > sz[big]) {
      big = v;
    }
  }
  for(auto [v, w] : adj[u]) {
    if(v == p || v == big) continue;
    filllight(v, u, dp);
    LineContainer nxtdp;
    dfs(v, u, nxtdp);
  }
 
  if(big != -1) {
    usedp(big, dp);
    dfs(big, u, dp);
  }
}