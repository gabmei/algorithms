template<typename T>
bool is_up(Point<T> u) {
  if(u.y > T(0)) return true;
  return u.y == T(0) && u.x >= T(0);
}
template<typename T>
bool polar_cmp(Point<T> u, Point<T> v) {
  if(is_up(u) == is_up(v)) return counterclockwise(u, v);
  return is_up(u) > is_up(v);
}
template<typename T>
bool same_half_plane(Point<T> u, Point<T> v) {
  if(cross(u, v) > T(0)) return true;
  return cross(u, v) == T(0) && dot(u, v) >= T(0);
}
