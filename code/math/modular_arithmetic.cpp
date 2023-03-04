const int MOD = 1e9 + 7;
template<typename T>
T bin_exp(T a, long long e){
  T r(1);
  for(; e > 0; e >>= 1){
    if(e & 1) r *= a;
    a *= a;
  }
  return r;
}
struct MB {
  int x;
  MB(int x = 0) : x(x < 0 ? x + MOD : x >= MOD ? x - MOD : x) {}
  MB& operator+=(const MB& rhs) {
    x += rhs.x;
    if(x >= MOD) x -= MOD;
    return *this;
  }
  MB& operator-=(const MB& rhs) {
    x -= rhs.x;
    if(x < 0) x += MOD;
    return *this; 
  }
  MB& operator*=(const MB& rhs) {
    long long y = 1ll * x * rhs.x;
    if(y >= MOD) y %= MOD;
    x = int(y);
    return *this;
  }
  MB& operator/=(const MB& rhs) {
    return *this *= bin_exp(rhs, MOD - 2);
  }
  friend MB operator+(MB lhs, const MB& rhs) { return lhs += rhs; }
  friend MB operator-(MB lhs, const MB& rhs) { return lhs -= rhs; }
  friend MB operator*(MB lhs, const MB& rhs) { return lhs *= rhs; }
  friend MB operator/(MB lhs, const MB& rhs) { return lhs /= rhs; }
  MB operator-() const { return MB() - *this; }
  bool operator==(const MB& rhs) const { return x == rhs.x; }
  bool operator!=(const MB& rhs) const { return !(*this == rhs); }
  friend ostream& operator<< (ostream& os, const MB& o) { return os << o.x; }
  friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};