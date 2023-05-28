vector<int> mosort(const vector<pair<int, int>>& query, const int B) {
  int q = (int)query.size();
  vector<pair<int ,int>> query_id(q);
  for(int i = 0; i < q; ++i) {
    auto [l, r] = query[i];
    auto x = l / B;
    auto y = x & 1 ? -r : +r;
    query_id[i] = {x, y};
  }
  vector<int> ord(q);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), [&](int i, int j) {
    return query_id[i] < query_id[j];
  });
  return ord;
}
int64_t xy2d_hilbert(int n, int x, int y) {
  int64_t d = 0;
  for (int s = n / 2; s > 0; s >>= 1) {
    int rx = (x & s) > 0;
    int ry = (y & s) > 0;
    d += s * s * ((3 * ry) ^ rx);
    if (rx == 0) {
      if (ry == 1) {
        x = s - 1 - x;
        y = s - 1 - y;
      }
      swap(x, y);
    }
  }
  return d;
}
vector<int> mosort_hilbert(int n, const vector<pair<int, int>>& query) {
  int k = n > 1 ? __lg(n - 1) + 1 : 0;
  n = 1 << k;
  int q = (int)query.size();
  vector<int64_t> id(q);
  for (int i = 0; i < q; i++) {
    auto [l, r] = query[i];
    id[i] = xy2d_hilbert(n, l, r);
  }
  vector<int> ord(q);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), [&](int i, int j) { 
    return id[i] < id[j];
  });
  return ord;
}
template<typename T, typename F>
vector<F> process_query(int n, const vector<T> a, const vector<pair<int, int>>& query) {
  auto ord = mosort_hilbert(n, query);
  //auto ord = mosort(query, sqrt(n) + 1);
  vector<F> ans(n);
  int mo_l = 0, mo_r = 0;
  F mo_ans{};
  auto add = [&](T x) {
    /* */
  };
  auto remove = [&](T x) {
    /* */
  };
  for(int i : ord) {
    auto [l, r] = query[i];
    while(mo_l > l) {
      add(a[--mo_l]);
    }
    while(mo_r < r) {
      add(a[mo_r++]);
    }
    while(mo_l < l) {
      remove(a[mo_l++]);
    }
    while(mo_r > r) {
      remove(a[--mo_r]);
    }
    ans[i] = mo_ans;
  }
  return ans;
}
