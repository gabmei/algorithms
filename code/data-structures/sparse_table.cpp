template<typename T, typename F>
struct SparseTable {
  int n;
  vector<vector<T>> st;
  vector<int> lg;
  F f;
  template<typename Iterator>
  SparseTable(Iterator first, Iterator last, F f = F()) : n(int(last - first)), lg(n + 1), f(f) {
    for(int j = 2; j <= n; ++j) {
      lg[j] = 1  + lg[j >> 1];
    }
    st.assign(lg[n] + 1, vector<T>(n));
    copy(first, last, begin(st[0]));
    for(int j = 0; j < lg[n]; ++j) {
      for(int i = 0; i + (1 << (j + 1)) <= n; ++i) {
        st[j + 1][i] = f(st[j][i], st[j][i + (1 << j)]);
      }
    }
  }
  T query(int l, int r) const {
    int j = lg[r - l];
    return f(st[j][l], st[j][r - (1 << j)]);
  }
};
template <typename T>
struct MinFunctor {
  T operator()(const T& x, const T& y) const { return min(x, y); }
};
template <typename T>
using RMQ = SparseTable<T, MinFunctor<T>>;