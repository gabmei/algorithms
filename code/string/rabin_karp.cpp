template<typename Mint>
struct RabinKarp {
  int n;
  vector<Mint> p, pw;
  RabinKarp() {}
  template<typename T>
  RabinKarp(const T& s, Mint C) : n(int(s.size())) {
    pw.assign(n + 1, 1);
    p.assign(n + 1, 0);
    for(int i = 1; i <= n; ++i) {
      pw[i] = pw[i - 1] * C;
      p[i] = p[i - 1] * C + s[i - 1];
    }
  }
  Mint hash(int i, int len) const {
    return (p[i + len] - pw[len] * p[i]);
  }
};
template<typename Mint>
struct Hash {
  int n;
  RabinKarp<Mint> rab[2], rev_rab[2];
  template<typename T>
  Hash(const T& s, Mint C0 = 727, Mint C1 = 137) : n((int)s.size()) {
    Mint C[2] = {C0, C1};
    auto rev_s = s;
    reverse(begin(rev_s), end(rev_s));
    for(int e = 0; e < 2; ++e) {
      rab[e] = RabinKarp<Mint>(s, C[e]);
      rev_rab[e] = RabinKarp<Mint>(rev_s, C[e]);
    }
  }
  pair<Mint, Mint> get_hash(int l, int r) const {
    return {rab[0].hash(l, r - l), rab[1].hash(l, r - l)};
  }
  pair<Mint, Mint> get_reverse_hash(int l, int r) const {
    return {rev_rab[0].hash(n - r, r - l), rev_rab[1].hash(n - r, r - l)};
  }
  bool is_palindrome(int l, int r) const {
    return get_hash(l, r) == get_reverse_hash(l, r);
  }
};
