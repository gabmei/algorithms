template<typename T, typename F>
struct MonoidQueue {
  deque<T> q;
  deque<pair<T, int>> m;
  F f;
  MonoidQueue(F f = F()) : f(f) {}
  void push(const T& x) {
    int last_min_dist = m.empty() ? 0 : 1;
    while(!m.empty() && f(x, m.back().first)) {
      last_min_dist += m.back().second;
      m.pop_back();
    }
    q.emplace_back(x);
    m.emplace_back(x, last_min_dist);
  }
  void pop() {
    if(q.front() == m.front().first) {
      m.pop_front();
    }
    q.pop_front();
    if(!m.empty()) {
      m.front().second -= 1;
    }
  }
  T front() const { return q.front(); }
  // return min / max value and its position
  pair<T, int> get_extremum() const { return m.front(); }
  bool empty() const { return q.empty(); }
};
template<typename T>
using MinQueue = MonoidQueue<T, std::less<T>>;
