const MB C[2] = {727, 137}; // double hashing
template<typename T = string>
struct RabinKarp {
  int n;
  vector<MB> p[2], pw[2];
  RabinKarp(const T& s = {}) : n(int(s.size())) {
    for(int e = 0; e < 2; ++e) {
      p[e].assign(n + 1, 0);
      pw[e].assign(n + 1, 1);
      for(int i = 1; i <= n; ++i) {
        pw[e][i] = pw[e][i - 1] * C[e];
        p[e][i] = p[e][i - 1] * C[e] + s[i - 1];
      }
    }
  }
  pair<int, int> hash(int i, int len) const {
    int h0 = (p[0][i + len] - pw[0][len] * p[0][i]).x;
    int h1 = (p[1][i + len] - pw[1][len] * p[1][i]).x;
    return {h0, h1};
  }
};
template<typename T>
struct Hash {
  RabinKarp<T> rab, rev_rab;
  Hash(const T& s) {
    auto rev_s = s;
    reverse(begin(rev_s), end(rev_s));
    rab = RabinKarp<T>(s);
    rev_rab = RabinKarp<T>(rev_s);
  }
  pair<int, int> getHash(int l, int r) const { return rab.hash(l, r - l + 1); }
  pair<int, int> getReverseHash(int l, int r) const { return rev_rab.hash(rev_rab.n - r - 1, r - l + 1); }
};
