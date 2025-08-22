// Line: A + t * d
// Segment: [A, B], B = A + 1 * d
// Beware degenerate cases: d = 0!
template<typename T>
struct Line {
  Point<T> A, d;
  Line(Point<T> A = Point<T>(), Point<T> d = Point<T>()) : A(A), d(d) {}
  Point<T> B() const { return A + d; }
  template<typename F>
  explicit operator Line<F>() const { return Line<F>(Point<F>(A), Point<F>(d)); };
};
template<typename T>
bool on_line(Point<T> P, Line<T> line) {
  return cross(P - line.A, line.d) == T(0);
}
template<typename T>
bool on_segment(Point<T> P, Line<T> seg) {
  return on_line(P, seg) && dot(seg.A - P, seg.B() - P) <= T(0);
}
template<typename T>
bool on_ray(Point<T> P, Line<T> ray) {
  return on_line(P, ray) && dot(P - ray.A, ray.d) >= T(0);
}
template<typename T = double>
T point_line_distance(Point<T> P, Line<T> line) {
  return abs(cross(line.d, P - line.A)) / norm(line.d);
}
template<typename T = double>
T point_segment_distance(Point<T> P, Line<T> seg) {
  if(dot(seg.d, P - seg.A) < T(0)) return norm(P - seg.A);
  if(dot(P - seg.B(), -seg.d) < T(0)) return norm(P - seg.B());
  return point_line_distance(P, seg);
}
template<typename T = double>
T point_ray_distance(Point<T> P, Line<T> seg) {
  if(dot(seg.d, P - seg.A) < T(0)) return norm(P - seg.A);
  return point_line_distance(P, seg);
}
template<typename T = double>
Point<T> line_projection(Point<T> P, Line<T> line) {
  return line.A + proj(P - line.A, line.d);
}
template<typename T>
bool collinear(Line<T> line1, Line<T> line2) {
  return cross(line1.d, line2.d) == T(0);
}
template<typename T>
bool same_line(Line<T> line1, Line<T> line2) {
  return collinear(line1, line2) && cross(line1.A - line2.A, line1.d) == T(0);
}
template<typename T = double>
T intersection_time(Line<T> line1, Line<T> line2) {
  return cross(line2.A - line1.A, line2.d) / cross(line1.d, line2.d);
}
template<typename T = double>
Point<T> line_intersection(Line<T> line1, Line<T> line2) {
  return line1.A + line1.d * intersection_time(line1, line2);
}
template<typename T = Double<double>>
vector<Point<T>> segment_segment_intersection(Line<T> seg1, Line<T> seg2) {
  vector<Point<T>> intersection;
  auto dd = cross(seg1.d, seg2.d);
  auto ls = cross(seg2.A - seg1.A, seg1.d);
  if(dd == T(0) && ls == T(0)) {
    if(dot(seg1.d, seg2.d) < T(0)) {
      seg2 = Line(seg2.B(), seg2.A - seg2.B());
    }
    Point<T> L = dot(seg2.A - seg1.A, seg1.d) < T(0) ? seg1.A : seg2.A;
    Point<T> R = dot(seg2.B() - seg1.B(), seg1.d) < T(0) ? seg2.B() : seg1.B();
    if(dot(R - L, seg1.d) >= T(0)) {
      intersection.emplace_back(L);
      if(L != R) intersection.emplace_back(R);
    }
  } else if(dd != T(0)) {
    auto rs = cross(seg2.A - seg1.A, seg2.d);
    if(dd < T(0)) dd = -dd, ls = -ls, rs = -rs;
    bool intersect = 0 <= ls && ls <= dd && 0 <= rs && rs <= dd;
    if(intersect) {
      intersection.emplace_back(seg1.A + seg1.d * rs / dd);
    }
  }
  return intersection;
}
template<typename T = Double<double>>
vector<Point<T>> circle_line_intersection(Point<T> C, T r, Line<T> line) {
  vector<Point<T>> intersections;
  Point<T> P = line_projection(C, line);
  T h = norm(P - C);
  if(h == r) {
    intersections.emplace_back(P);
  } else if(h < r) {
    T x = sqrt(r * r - h * h);
    line.d = line.d / norm(line.d);
    for(T d : {-1, +1}) {
      intersections.emplace_back(P + line.d * (d * x));
    }
  }
  return intersections;
}
template<typename T = Double<double>>
vector<Point<T>> circle_circle_intersection(Point<T> C1, T r1, Point<T> C2, T r2) {
  if(C1 == C2) return {};  
  T a = 2 * (C1.x - C2.x);
  T b = 2 * (C1.y - C2.y);
  T c = (dot(C2, C2) - r2 * r2) - (dot(C1, C1) - r1 * r1);
  Line<T> line;
  if(a == T(0)) {
    line = Line(Point<T>(0, -c / b), Point<T>(1, 0)); 
  } else if(b == T(0)) {
    line = Line(Point<T>(-c / a, 0), Point<T>(0, 1));
  } else {
    line = Line(Point<T>(0, -c / b), Point<T>(b, -a));
  }
  return circle_line_intersection(C1, r1, line);
}
template<typename T = Double<double>>
vector<Point<T>> circle_point_tangent(Point<T> C, T r, Point<T> P) {
  vector<Point<T>> tg;
  T d = norm(C - P);
  T xx = dot(C - P, C - P) - r * r;
  if(xx == T(0)) {
    tg.emplace_back(P);
  } else if(xx > T(0)) {
    T x = sqrt(xx);
    Point<T> u = (C - P) * (x / d);
    Point<T> A = P + rotateCCW<T>(u, acos(x / d));
    Point<T> B = P + rotateCCW<T>(u, -acos(x / d));
    tg.emplace_back(A);
    tg.emplace_back(B);
  }
  return tg;
}
