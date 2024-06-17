using dt = long double;
const dt gr = (sqrt(5) + 1) / 2, EPS = 1e-7;
template<typename F>
dt golden_ratio_search(dt lo, dt hi, F&& f) {
  dt x1 = hi - (gr - 1) * (hi - lo), x2 = lo + (gr - 1) * (hi - lo);
  dt f1 = f(x1), f2 = f(x2);
  for(; hi - lo > EPS;) {
    if(f1 > f2) {
      hi = x2; x2 = x1; f2 = f1;
      x1 = hi - (gr - 1) * (hi - lo);
      f1 = f(x1);
    } else {
      lo = x1; x1 = x2; f1 = f2;
      x2 = lo + (gr - 1) * (hi - lo);
      f2 = f(x2);
    }
  }
  return x1;
}
