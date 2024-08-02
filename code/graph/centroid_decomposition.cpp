vector<int> adj[MAXN]; int sz[MAXN]; bool blocked[MAXN];
int preprocess(int u, int p) {
  sz[u] = 1;
  for(auto v : adj[u]) {
    if(v == p || blocked[v]) continue;
    sz[u] += preprocess(v, u);
  }
  return sz[u];
}
int get_centroid(int u, int p, int tree_size) {
  for(auto v : adj[u]) {
    if(v == p || blocked[v]) continue;
    if(2 * sz[v] >= tree_size) return get_centroid(v, u, tree_size);
  }
  return u;
}
void centroid_decomposition(int u, int lst_c) {
  int c = get_centroid(u, -1, preprocess(u, -1));
  blocked[c] = true;
  /* do something with centroid c */
  for(auto v : adj[c]) {
    if(!blocked[v]) centroid_decomposition(v, c);
  }
}
