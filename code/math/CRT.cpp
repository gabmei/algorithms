template <typename T>
T extended_gcd(T a, T b, T& x, T& y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  } else {
    T q = b / a, r = b % a;
    T g = extended_gcd(r, a, y, x);
    x -= q * y;
    return g;
  }
}
template<typename T>
T mul(T a, T b, T m) {
  T q = (long double) a * b / m;
  T r = a * b - q * m;
  return (r + m) % m;
}
template <typename T>
struct CRT {
  T a, mod;
  CRT() : a(0), mod(1) {}
  CRT(T a_, T mod_) : a(a_), mod(mod_) {
    a %= mod;
    if (a < 0) a += mod;
  } 
  CRT operator+(CRT rhs) const {
    T x, y;
    T g = extended_gcd(mod, rhs.mod, x, y);
    if (a == -1 || rhs.a == -1 || (a - rhs.a) % g) {
      CRT res;
      res.a = -1;
      return res;
    }
    T lcm = mod / g * rhs.mod;
    return CRT(a + mul(mul(mod, x, lcm), (rhs.a - a) / g, lcm), lcm);
  }
};
