struct DisjointSetUnion {
  vector<int> p;
  DisjointSetUnion(int n) : p(n, -1) {}
  int root(int a) { return p[a] < 0 ? a : p[a] = root(p[a]); }
  int size(int x) { return -p[root(x)]; }
  bool unite(int a, int b) {
    a = root(a), b = root(b);
    if(a == b) {
      return false;
    }
    if(size(a) < size(b)) {
      swap(a, b);
    }
    p[a] += p[b];
    p[b] = a;
    return true;
  }
};