ll cost(int l, int r) { /* transition cost for l...r (inclusive)*/ }
// dp[i][j] = min_i{0 <= k <= j}(dp[i - 1][k - 1] + cost(k, j))
// condition for it: opt(i, j) <= opt(i, j + 1)
// special case to check: cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c) a <= b <= c <= d 
// computes dp[i][l]...dp[i][r] (inclusive)
// alternativaly, maintain cost function for [opt_l, r] during recursion
void divide_and_conquer(int e, int l, int r, int opt_l, int opt_r) {
  if(l > r) return;
  int mid = (l + r) / 2;
  pair<ll, int> best = {INF, -1};
  for(int k = opt_l; k <= min(opt_r, mid); ++k) {
    ll cur = (k > 0 ? dp[k - 1][e^1] : 0) + cost(k, mid);
    if(cur < best.first) {
      best = {cur, k};
    }
  }
  dp[mid][e] = best.first;
  divide_and_conquer(e, l, mid - 1, opt_l, best.second);
  divide_and_conquer(e, mid + 1, r, best.second, opt_r);
}
for(int i = 0; i < n; ++i) dp[i][0] = cost(0, i); // initial cost
for(int i = 1; i < k; ++i) divide_and_conquer(i % 2, 0, n - 1, 0, n - 1);
