template<typename T>
vector<Point<T>> convex_hull(vector<Point<T>> pts) {
  sort(pts.begin(), pts.end());
  pts.erase(unique(begin(pts), end(pts)), end(pts));
  if(pts.size() <= 2) return pts;
  vector<Point<T>> upper(pts.size()), lower(pts.size());
  int k = 0, l = 0;
  for (auto p : pts) {
    while (k > 1 && !clockwise(upper[k - 1] - upper[k - 2], p - upper[k - 1])) k -= 1;
    while (l > 1 && !counterclockwise(lower[l - 1] - lower[l - 2], p - lower[l - 1])) l -= 1;
    upper[k++] = lower[l++] = p;
  }
  upper.resize(k - 1), lower.resize(l);
  lower.insert(lower.end(), upper.rbegin(), upper.rend() - 1);
  return lower;
}

template<typename T>
int maximize_dot_product(const vector<Point<T>>& h, const Point<T>& vec) {
  int n = (int)h.size();
  int ans = 0;
  for(int rep = 0; rep < 2; ++rep) {
    int lo = 0, hi = n - 1;
    while(lo < hi) {
      int mid = (lo + hi) / 2;
      auto d1 = dot(h[mid + 1] - h[0], vec), d2 = dot(h[mid + 1] - h[mid], vec);
      bool check = d2 > T(0);
      if(rep == 0) check = check && d1 > T(0);
      else check = check || d1 - d2 <= T(0);
 
      if(check) lo = mid + 1;
      else hi = mid;
    }
    if(dot(h[ans], vec) < dot(h[lo], vec)) ans = lo;
  }
  return ans;
}
