struct DisjointSetUnion {
  vector<int> p;
  vector<vector<int>> l;
  DisjointSetUnion(int n) : p(n), l(n) {
    for(int i = 0; i < n; ++i) {
      p[i] = i;
      l[i] = {i};
    }
  }
  int root(int a) { return p[a]; }
  bool unite(int a, int b) {
    a = root(a); b = root(b);
    if(a == b) {
      return false;
    }
    if(l[a].size() < l[b].size()) {
      swap(a,b);
    }
    while(!l[b].empty()) {
      int u = l[b].back();
      p[u] = a;
      l[a].push_back(u);
      l[b].pop_back();
    }
    return true;
  }
};