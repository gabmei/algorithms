template<typename T>
struct Poly {
  int n;
  vector<T> v;
  Poly(int n) : n(n), v(n, 0) {}
  friend Poly operator*(const Poly& lhs, const Poly& rhs) {
    int n = (int)lhs.n;
    Poly ans(n);
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
        ans.v[(i + j) % n] += lhs.v[i] * rhs.v[j];
      }
    }
    return ans;
  }
  void set_identity() {
    v[0] = T(1);
    for(int i = 1; i < n; ++i) {
      v[i] = T(0);
    }
  }
};
template<typename T>
Poly<T> poly_exp(Poly<T> a, long long e) {
  Poly<T> r(a.n);
  r.set_identity();
  for(; e > 0; e >>= 1) {
    if(e & 1) {
      r = r * a;
    }
    a = a * a;
  }
  return r;
}
