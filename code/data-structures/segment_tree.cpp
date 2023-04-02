struct Node {
  int x; //atributes
  Node() : x(0) {} //empty constructor
  Node(int x) : x(x) {} // init
  Node& operator+=(const Node& rhs) { // merge function
    /* addition of rhs to *this here */
    return *this;
  }
  friend Node operator+(Node lhs, const Node& rhs) {
    return lhs += rhs;
  }
};

template<typename T>
struct SegmentTree {
public:
  SegmentTree(int n = 0) : n(n), st(4 * n, T()) {}
  template<typename Iterator>
  SegmentTree(Iterator first, Iterator last) : SegmentTree(int(last - first)) {
    build(1, 0, n, first);
  }
  void update(int x, const T& val) {
    update(1, 0, n, x, val);
  }
  T query(int l, int r) {
    T cur{}; 
    query(1, 0, n, l, r, cur);
    return cur;
  }
private:
  int n;
  vector<T> st;
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
  void update(int p, int tl, int tr, int x, const T& val) {
    if(tl + 1 == tr) {
      st[p] += val;
    } else {
      int mid = (tl + tr) / 2;
      if(x < mid) {
        update(left(p), tl, mid, x, val);
      } else {
        update(right(p), mid, tr, x, val);
      }
      st[p] = st[left(p)] + st[right(p)];
    }
  }
  void query(int p, int tl, int tr, int l, int r, T& cur) const {
    if(tl >= r || tr <= l) {
      return;
    } else if(tl >= l && tr <= r) {
      cur += st[p];
    } else {
      int mid = (tl + tr) / 2;
      query(left(p), tl, mid, l, r, cur);
      query(right(p), mid, tr, l, r, cur);
    }
  }
};