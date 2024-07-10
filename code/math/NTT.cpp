const uint32_t MOD = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
template<typename Mint>
void ntt(vector<Mint> &a) {
	int n = (int)a.size(), L = 31 - __builtin_clz(n);
	static vector<Mint> rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		Mint z[] = {1, bin_exp(Mint(root), MOD >> s)};
    for(int i = k; i < 2 * k; ++i) rt[i] = rt[i / 2] * z[i & 1];
	}
	vector<int> rev(n);
	for(int i = 0; i < n; ++i) {
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    if(i < rev[i]) swap(a[i], a[rev[i]]);
  }
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) 
      for(int j = 0; j < k; ++j) {
			  Mint z = rt[j + k] * a[i + j + k], &ai = a[i + j];
        a[i + j + k] = ai - z;
        ai += z;
      }
}
template<typename Mint>
vector<Mint> convolution(const vector<Mint> &a, const vector<Mint> &b) {
	if (a.empty() || b.empty()) return {};
	int s = (int)a.size() + (int)b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	Mint inv = 1 / Mint(n);
	vector<Mint> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for(int i = 0; i < n; ++i) out[-i & (n - 1)] = L[i] * R[i] * inv;
	ntt(out);
  out.resize(s);
  return out;
}
