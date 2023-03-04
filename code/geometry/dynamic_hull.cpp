template<typename T>
struct DynamicHull {
  set<T> hull;
  bool inside_hull(const T& p) const {
    auto it = hull.lower_bound(p);
    if(it == hull.end()) {
      return false;
    }
    if(it == hull.begin()) {
      return p.y <= (*it).y;
    }
    auto prv = prev(it);
    return cmp(cross(p - (*prv), (*it) - p)) >= 0;  
  }
  void insert(const T& p) {
    auto [x, y] = p;
    update(p);
    update(T(0, y));
  }
private:
  void update(const T& p) {
    if(inside_hull(p)) {
      return;
    }
    hull.insert(p);
    auto it = hull.lower_bound(p);
    it = update_left(it);
    update_right(it);
  }
  template<typename Iterator>
  Iterator update_left(Iterator it) {
    if(it == hull.begin()) {
      return it;
    }
    auto prv = prev(it);
    if(prv == hull.begin()) {
      return it;
    }
    auto first_delete = it;
    while(prv != hull.begin()) {
      auto prvprv = prev(prv);
      auto sgn = cmp(cross((*prv) - (*prvprv), (*it) - (*prv))) >= 0;
      if(sgn > 0) {
        first_delete = prv;
      } else {
        break;
      }
      prv = prvprv;
    }
    return hull.erase(first_delete, it);
  }
  template<typename Iterator>
  Iterator update_right(Iterator it) {
    auto nxt = next(it);
    if(nxt == hull.end()) {
      return it;
    }
    auto last_delete = it;
    while(next(nxt) != hull.end()) {
      auto nxtnxt = next(nxt);
      auto sgn = cmp(cross((*nxt) - (*it), (*nxtnxt) - (*nxt))) >= 0;
      if(sgn > 0) {
        last_delete = nxt;
      } else {
        break;
      }
      nxt = nxtnxt;
    }
    return hull.erase(next(it), next(last_delete));
  }
};