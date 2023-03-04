struct Line {
  ll m, c;
  Line(ll m, ll _c) : m(m), c(c) {}
  ll eval(ll x) {
    return m * x + c;
  }
};
struct CHT {
  vector<Line> lines;
  bool obsolete(Line a, Line b, Line c) {
    return 1.d * (c.c - a.c)*(a.m - b.m) > 1.d * (b.c - a.c)*(a.m - c.m);
  }
  void insert(Line line) {
    int sz = (int)lines.size();
    for(; sz > 1; --sz) {
      if(obsolete(lines[sz - 2], lines[sz - 1], line)) {
        lines.pop_back();
        continue;
      }
      break;
    }
    lines.emplace_back(line);
  }
  ll query(ll x) {
    int lo = 0, hi = (int)lines.size() - 1;
    while(hi - lo > 0) {
      int mid = (lo + hi) / 2;
      if(lines[mid].eval(x) > lines[mid + 1].eval(x)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return lines[lo].eval(x);
  }
};