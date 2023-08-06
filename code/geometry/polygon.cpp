template<typename T>
bool same_side(Point<T> P, Point<T> A, Point<T> B, Point<T> C) {
  T u = cross(B - A, P - A);
  T v = cross(B - A, C - A);
  int x = u == T(0) ? 0 : u < T(0) ? -1 : +1;
  int y = v == T(0) ? 0 : v < T(0) ? -1 : +1;
  return x * y >= 0;
}
template<typename T>
bool point_inside_triangle(Point<T> P, Point<T> A, Point<T> B, Point<T> C) {
  return same_side(P, A, B, C) && same_side(P, B, C, A) && same_side(P, C, A, B);
}
// polygon must be ordered counterclockwise
template<typename T>
bool point_inside_convex_polygon(Point<T> P, const vector<Point<T>>& poly) {
  if(poly.size() == 1) return P == poly[0];
  if(poly.size() == 2) return on_segment(P, Line(poly[0], poly[1] - poly[0]));
  int l = 1, r = (int)poly.size() - 1;
  while(r - l > 1) {
    int m = (l + r) / 2;
    if(clockwise(poly[m] - poly[0], P - poly[0])) {
      r = m;
    } else {
      l = m;
    }
  }
  return point_inside_triangle(P, poly[0], poly[l], poly[l + 1]);
}
template<typename T>
double polygon_area(const vector<Point<T>>& poly) {
  double area = 0;
  for(int i = 0, n = (int)poly.size(); i < n; ++i) {
    int j = i + 1 == n ? 0 : i + 1;
    area += cross(poly[i], poly[j]);
  }
  return abs(area) / 2;
}
