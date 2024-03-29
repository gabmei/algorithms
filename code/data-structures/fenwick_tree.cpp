template<typename T>
struct FenwickTree {
  static int lsb(int b) { return b & -b; }
  int n;
  vector<T> ft;
  FenwickTree(int n = 0) : n(n), ft(n + 1, T()) {}
  template<typename Iterator>
  FenwickTree(Iterator first, Iterator last) : FenwickTree(int(last - first)) {
    for (int i = 0; i < n; ++i) {
      ft[i + 1] = first[i] + ft[i];
    }
    for (int i = n; i >= 1; --i) {
      ft[i] -= ft[i - lsb(i)];
    }
  }
  void update(int x, const T& val) {
    for(++x; x <= n; x += lsb(x)) {
      ft[x] += val; 
    }
  }
  T query(int x) const { //query on [0,x)
    T ret{};
    for(; x > 0; x -= lsb(x)) {
      ret += ft[x];
    }
    return ret;
  }
  T query(int l, int r) const { // query on [l,r)
    if(l + 1 == r) {
      ++l;
      T ret = ft[r--];
      for(l -= lsb(l); l != r; r -= lsb(r)){
        ret -= ft[r];
      }
      return ret;
    }
    return query(r) - query(l);
  }
  // Returns largest r such that pred(query(0, r)) == true (or n if none)
  template <typename Pred>
  int find_right(Pred&& pred) const {
    T prefix{};
    int pos = 0;
    for (int x = __lg(n); x >= 0; --x) {
      int npos = pos + (1 << x);
      if (npos > n) {
        continue;
      }
      T nprefix = prefix + ft[npos];
      if (pred(nprefix)) {
        pos = npos;
        prefix = nprefix;
      }
    }
    return pos;
  }
  int lower_bound(T value){ 
    return find_right([value](T x){ return x < value; });
  }
};
