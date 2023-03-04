const double EPS = 1e-8;
template <typename T>
int cmp(T a, T b = 0);

template<>
int cmp<double>(double a, double b) {
  if (abs(a - b) < EPS) return 0;
  return a < b ? -1 : +1;
}
template<>
int cmp<long long>(long long a, long long b) {
  if (a == b) return 0;
  return a < b ? -1 : +1;
}
template<typename T>
struct PT {
  T x, y;
  PT(T x = 0, T y = 0) : x(x), y(y) {}
  PT& operator += (const PT& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  PT& operator -=(const PT& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  friend PT operator +(PT lhs, const PT& rhs) { return lhs += rhs; }
  friend PT operator -(PT lhs, const PT& rhs) { return lhs -= rhs; }
  PT operator *(T c) const { return PT(x * c, y * c); }
  PT operator /(T c) const { return PT(x / c, y / c); }
  bool operator <(const PT &p) const {
    if(cmp(x, p.x) != 0) return x < p.x;
    return cmp(y, p.y) < 0;
  }
  template<typename F>
  explicit operator PT<F>() const {
    return PT<F>(F(x), F(y));
  }
  friend ostream& operator<< (ostream& os, const PT& o) { return os << o.x << ' ' << o.y; }
  friend istream& operator>> (istream& is, PT& o) { return is >> o.x >> o.y; }
};
template<typename T>
T dot (PT<T> p, PT<T> q) { return p.x * q.x + p.y*q.y; }
template<typename T>
T cross (PT<T> p, PT<T> q) { return p.x * q.y - p.y*q.x; }