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
  Point operator-() const { return Point() - *this; }
  Point operator*(T c) const { return Point(x * c, y * c); }
  Point operator/(T c) const { return Point(x / c, y / c); }
  bool operator<(const Point& rhs) const {
    if(x == rhs.x) return y < rhs.y;
    return x < rhs.x;
  }
  bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Point& rhs) const { return !(*this == rhs); }
  template<typename F>
  explicit operator Point<F>() const { return Point<F>(F(x), F(y)); }
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
template<typename T = double>
T norm(Point<T> u) { return sqrt(dot(u, u)); }
template<typename T = double>
Point<T> proj(Point<T> u, Point<T> v) {
  return v * (dot(u, v) / dot(v, v));
}
template<typename T>
bool counterclockwise(Point<T> u, Point<T> v) { return cross(u, v) > T(0); }
template<typename T>
bool clockwise(Point<T> u, Point<T> v) { return cross(u, v) < T(0); }
template<typename T>
Point<T> rotateCCW90(Point<T> u) { return Point<T>(-u.y, u.x); }
template<typename T>
Point<T> rotateCW90(Point<T> u) { return Point<T>(u.y, -u.x); }
template<typename T = double>
Point<T> rotateCCW(Point<T> u, T t) {
  return Point<T>(u.x * cos(t) - u.y * sin(t), u.x * sin(t) + u.y * cos(t));
}
template<typename T = double>
T angle(Point<T> u, Point<T> v) {
  return acos(dot(u, v) / (norm(u) * norm(v)));
}