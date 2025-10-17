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
};
template<typename T>
struct SegmentTree {
public:
  SegmentTree(int n) : n(n), st(2 * n, T()) {}
  template<typename Iterator>
  SegmentTree(Iterator first, Iterator last) : SegmentTree(int(last - first)) {
    copy(first, last, begin(st) + n);
    for(int p = n - 1; p > 0; --p) {
      st[p] = st[left(p)] + st[right(p)];
    }
  }
  void update(int p, const T& val) {
    p += n;
    st[p] = val;
    for(p /= 2; p > 0; p /= 2) {
      st[p] = st[left(p)] + st[right(p)];
    }
  }
  T query(int l, int r) const {
    T lp{}, rp{};
    for(l += n, r += n; l < r; l /= 2, r /= 2) {
      if(l & 1) {
        lp += st[l++];
      }
      if(r & 1) {
        rp = st[--r] + rp;
      }
    }
    return lp + rp;
  }
private:
  int n;
  vector<T> st;
  static int left(int p) { return 2 * p; }
  static int right(int p) { return 2 * p + 1; }
};
