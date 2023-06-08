template<typename T>
long long sq(T a) { return 1ll * a * a; }
template<typename T>
long long dist(pair<T, T> a, pair<T, T> b) {
  return sq(a.first - b.first) + sq(a.second - b.second);
}
template<typename T>
long long divide_and_conquer(const vector<pair<T, T>>& px, const vector<pair<T, T>>& py) {
  int n = (int)px.size();
  auto min_distance = numeric_limits<long long>::max();
  if(n == 1) {
    return min_distance;
  }
  auto lx = vector(begin(px), begin(px) + n / 2);
  auto rx = vector(begin(px) + n / 2, end(px));
  vector<pair<T, T>> ly, ry;
  auto pivot = px[n / 2 - 1];
  for(auto p : py) {
    if(p < pivot) {
      ly.emplace_back(p);
    } else {
      ry.emplace_back(p);
    }
  }
  auto ld = divide_and_conquer(lx, ly);
  auto rd = divide_and_conquer(rx, ry);
  min_distance = min(ld, rd);
  vector<pair<T, T>> stripe;
  for(auto p : py) {
    if(sq(p.first - pivot.first) < min_distance) {
      stripe.emplace_back(p);
    }
  }
  for(int i = 0, len = (int)stripe.size(); i < len; ++i) {
    for(int j = i + 1; j < len && sq(stripe[i].second - stripe[j].second) < min_distance; ++j) {
      min_distance = min(min_distance, dist(stripe[i], stripe[j]));
    }
  }
  return min_distance;
}
template<typename T>
long long closest_pair(vector<pair<T, T>> px) {
  auto py = px;
  sort(begin(px), end(px));
  sort(begin(py), end(py), [](auto a, auto b) {
    return tie(a.second, a.first) < tie(b.second, b.first);
  });
  return divide_and_conquer(px, py);
}
