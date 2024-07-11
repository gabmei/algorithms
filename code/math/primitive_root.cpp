const uint32_t MOD = (119 << 23) + 1;
using Mint = Mod<MOD>;
// is r a primitive root of MOD
bool primitive_root(int r) {
  int m = MOD - 1;
  for(int i = 2; i * i <= m; ++i) {
    if(m % i == 0) {
      if(bin_exp(Mint(r), i) == 1) return false;
      if(bin_exp(Mint(r), m / i) == 1) return false;
    }
  }
  return true;
}
