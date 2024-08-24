vector<int> L(n, 0), R(n, q);
for(int l = 0; l < 20; ++l) {
  vector<vector<int>> on(q);
  for(int i = 0; i < n; ++i) {
    if(L[i] == R[i]) continue;
    int m = (L[i] + R[i])/ 2;
    on[m].emplace_back(i);
  }
  // initialize some structure
  auto add = [&](int i) { /* add i-th element to the data structure */ };
  auto check = [&](int i) { /* check condition for current prefix of elements to the i-th query */ };
  for(int m = 0; m < q; ++m) {
    add(m); // maintain prefix of elements
    for(auto i : on[m]) {
      if(check(i)) R[i] = m;
      else L[i] = m + 1;
    }
  }
}
