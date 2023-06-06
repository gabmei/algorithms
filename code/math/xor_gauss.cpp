template<const int N, class T = unsigned int>
struct XorGauss {
  T basis[N]{};
  int sz = 0;
  T reduce(T x) const {
    for(int i = N - 1; i >= 0; --i) {
      x = std::min(x, x ^ basis[i]);
    }
    return x;
  }
  T augment(T x) const { 
    return ~reduce(~x);
  }
  bool add(T x) {
    for(int i = N - 1; i >= 0; --i) {
      if(((x >> i) & 1) == 0) {
        continue;
      }
      if(basis[i]) {
        x ^= basis[i];
      } else {
        basis[i] = x;
        sz += 1;
        return true;
      }
    }
    return false;
  }
};
