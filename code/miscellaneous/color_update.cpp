template<typename T, typename Color>
struct ColorUpdate {
  struct Range {
    T l, r;
    Color v;
    Range(T l) : l(l) {}
    Range(T l, T r, Color v) : l(l), r(r), v(v) {}
    bool operator<(const Range& rhs) const { return l < rhs.l; }
  };
  set<Range> ranges;
  template<typename F>
  Range update(T l, T r, Color v, F&& get) {
    auto it = ranges.lower_bound(l);
    if(it != ranges.begin()) {
      if(prev(it)->r > l) {
        --it;
        auto cur = *it;
        it = ranges.erase(it);
        it = ranges.emplace_hint(it, cur.l, l, cur.v);
        it = ranges.emplace_hint(it, l, cur.r, cur.v);
      }
    }
    for(; it != ranges.end() && it->r <= r;) {
      auto cur = *it;
      it = ranges.erase(it);
      get(cur.l, cur.r, cur.v);
    }
    if(it != ranges.end()) {
      if(it->l < r) {
        auto cur = *it;
        it = ranges.erase(it);
        get(cur.l, r, cur.v);
        it = ranges.emplace_hint(it, r, cur.r, cur.v);
      }
    }
    it = ranges.emplace_hint(it, l, r, v);
    return Range(l, r, v);
  }
};