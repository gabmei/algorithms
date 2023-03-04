map<vector<int>, int> hasher;
int hashify(vector<int> x) {
  sort(begin(x), end(x));
  if(!hasher[x]) {
    hasher[x] = (int)hasher.size();
  }
  return hasher[x];
}
int get_hash(int u, int p) { // get a "hash" of v's subtree
  vector<int> children;
  for(int v: g[u]) {
    if(v == p) {
      continue
    }
    children.push_back(get_hash(v, u));
  }
  return hashify(children);
}