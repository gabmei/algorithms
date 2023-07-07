template<typename T>
struct Point {
  T x, y, z;
  Point(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
  Point operator+(const Point& o) const { return Point(x + o.x, y + o.y, z + o.z);}
  Point operator-(const Point& o) const { return Point(x - o.x, y - o.y, z - o.z);}
  friend ostream& operator<<(ostream& os, const Point& o) { return os << o.x << ' ' << o.y << ' ' << o.z; }
  friend istream& operator>>(istream& is, Point& o) { return is >> o.x >> o.y >> o.z; }
  template<typename F>
  operator Point<F>() const {
    return Point<F>(F(x), F(y), F(z));
  }
};
template<typename T>
T dot(Point<T> u, Point<T> v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
template<typename T>
Point<T> cross(Point<T> u, Point<T> v) {
  return Point(u.y * v.z - u.z * v.y, -u.x * v.z + v.x * u.z, u.x * v.y - v.x * u.y);
}
// returns if P is on the plane determined by vectors u and v
bool point_on_plane(Point<__int128_t> u, Point<__int128_t> v, Point<__int128_t> P) {
  auto w = cross(u, v);
  return dot(w, P) == 0;
}
bool same_side(Point<__int128_t> a, Point<__int128_t> b, Point<__int128_t> c, Point<__int128_t> P) {
  auto u = cross(b - a, c - a);
  auto v = cross(b - a, P - a);
  return dot(u, v) >= 0;
}
bool point_inside_triangle(Point<int> a, Point<int> b, Point<int> c, Point<int> P) {
  if(!point_on_plane(b - a, c - a, P - a)) {
    return false;
  }
  return same_side(a, b, c, P) && same_side(b, c, a, P) && same_side(c, a, b, P);
}
