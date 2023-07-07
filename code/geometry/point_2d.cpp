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
struct Point {
  T x, y;
  Point(T x = 0, T y = 0) : x(x), y(y) {}
  Point operator+(const Point& rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator-(const Point& rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  Point operator*(T c) const { return Point(x * c, y * c); }
  Point operator/(T c) const { return Point(x / c, y / c); }
  bool operator<(const Point& rhs) const {
    if(cmp(x, rhs.x) != 0) return x < rhs.x;
    return cmp(y, rhs.y) < 0;
  }
  bool operator==(const Point& rhs) const {
    return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0;
  }
  template<typename F>
  explicit operator Point<F>() const {
    return Point<F>(F(x), F(y));
  }
  friend ostream& operator<<(ostream& os, const Point& o) {
    return os << o.x << ' ' << o.y;
  }
  friend istream& operator>>(istream& is, Point& o) {
    return is >> o.x >> o.y;
  }
};
template<typename T>
T dot(Point<T> u, Point<T> v) { return u.x * v.x + u.y * v.y; }
template<typename T>
T cross(Point<T> u, Point<T> v) { return u.x * v.y - u.y * v.x; }
