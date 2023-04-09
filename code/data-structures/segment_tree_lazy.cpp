struct LazyContext {
  int x;
  bool is_empty;
  LazyContext() : x(0), is_empty(true) {} // neutral element
  LazyContext(int x) : x(x), is_empty(false) {}
  void compose(const LazyContext& rhs) {
    /* addition to *this */
    is_empty &= rhs.is_empty;
  }
  bool empty() const { return is_empty; }
  void reset() { *this = LazyContext(); }
};
struct Node {
  int x;
  Node() : x(0) {} // neutral element
  Node(int x) : x(x) {}
  Node& operator+=(const Node& rhs) {
    /* addition to *this */
    return *this;
  }
  friend Node operator+(Node lhs, const Node& rhs) { 
    return lhs += rhs;
  }
  void apply(const LazyContext& lazy) {
    /* update node with lazy */
  }
};
template<typename T, typename L>
struct LazySegmentTree {
public:
  LazySegmentTree(int n = 0) : n(n), st(4 * n, T()), lazy(4 * n, L()) {}
  template<typename Iterator>
  LazySegmentTree(Iterator first, Iterator last) : LazySegmentTree(int(last - first)) {
    build(1, 0, n, first);
  }
  void update(int l, int r, const L& val) {
    update(1, 0, n, l, r, val);
  }
  T query(int l, int r) {
    T cur{};
    query(1, 0, n, l, r, cur);
    return cur;
  }
private:
  int n;
  vector<T> st;
  vector<L> lazy;
  static int left (int p) { return 2 * p; }
  static int right (int p) { return 2 * p + 1; }
  template<typename Iterator>
  void build(int p, int tl, int tr, Iterator first) {
    if(tl + 1 == tr) {
      st[p] = first[tl];
    } else {
      int mid = (tl + tr) / 2;
      build(left(p), tl, mid, first);
      build(right(p), mid, tr, first);
      st[p] = st[left(p)] + st[right(p)];
    }
  }
  void update(int p, int tl, int tr, int l, int r, const L& val) {
    if(tl >= r || tr <= l) {
      return;
    } else if(tl >= l && tr <= r) {
      st[p].apply(val);
      lazy[p].compose(val);
    } else {
      push(p);
      int mid = (tl + tr) / 2;
      update(left(p), tl, mid, l, r, val);
      update(right(p), mid, tr, l, r, val);
      st[p] = st[left(p)] + st[right(p)];
    }
  }
  void query(int p, int tl, int tr, int l, int r, T& cur) {
    if(tl >= r || tr <= l) {
      return;
    } else if(tl >= l && tr <= r) {
      cur += st[p];
    } else {
      push(p);
      int mid = (tl + tr) / 2;
      query(left(p), tl, mid, l, r, cur);
      query(right(p), mid, tr, l, r, cur);
    }
  }
  void push(int p) {
    if(lazy[p].empty()) {
      return;
    }
    for(int q : {left(p), right(p)}) {
      st[q].apply(lazy[p]);
      lazy[q].compose(lazy[p]);
    }
    lazy[p].reset();
  }
};
