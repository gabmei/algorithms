const double EPS = 1e-9;
template<typename T = double>
int sign(T x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : +1; }
template<typename T = double>
struct Double {
  T x;
  Double(T x = 0) : x(x) {}
  bool operator==(Double rhs) const { return sign(x - rhs.x) == 0; }
  bool operator!=(Double rhs) const { return sign(x - rhs.x) != 0; }
  bool operator<(Double rhs)  const { return sign(x - rhs.x)  < 0; }
  bool operator<=(Double rhs) const { return sign(x - rhs.x) <= 0; }
  bool operator>(Double rhs)  const { return sign(x - rhs.x)  > 0; }
  bool operator>=(Double rhs) const { return sign(x - rhs.x) >= 0; }
  friend ostream& operator<<(ostream& os, const Double& o) { return os << o.x; }
  friend istream& operator>>(istream& is, Double& o) { return is >> o.x; }
  operator T() const { return x; } // implicit conversion
};
using DT = Double<long double>;
// make sure comparisons are always between same type
// avoid problems with implicit conversion