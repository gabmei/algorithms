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
