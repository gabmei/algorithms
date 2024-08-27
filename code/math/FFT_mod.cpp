template<const int MOD, typename T = long long>
vector<T> convolution_mod(const vector<T>& a, const vector<T>& b) {
  if (a.empty() || b.empty()) return {};
  vector<T> res((int)a.size() + (int)b.size() - 1);
  int B = 32 - __builtin_clz((int)res.size()), n = 1 << B, cut = int(sqrt(MOD));
  vector<Complex> L(n), R(n), outs(n), outl(n);
  for(int i = 0; i < (int)a.size(); ++i) L[i] = Complex((int)a[i] / cut, (int)a[i] % cut);
  for(int i = 0; i < (int)b.size(); ++i) R[i] = Complex((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i = 0; i < n; ++i) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i = 0; i < (int)res.size(); ++i) {
		T av = (T)llround(real(outl[i])), cv = (T)llround(imag(outs[i]));
		T bv = (T)llround(imag(outl[i])) + (T)llround(real(outs[i]));
		res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
	}
  return res;
}
