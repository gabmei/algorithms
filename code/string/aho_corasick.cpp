struct AhoType {
  static const int ALPHA = 26;
  static int f(char c) { return c - 'a'; }
};
template<typename AhoType>
struct AhoCorasick {
  struct Node {
    int nxt[AhoType::ALPHA] {};
    int p = 0, ch = 0, len = 0;
    int link = 0;
    int occ_link = 0;
    Node(int p = 0, int ch = 0, int len = 0) : p(p), ch(ch), len(len) {}
  };
  vector<Node> tr;
  AhoCorasick() : tr(1) {}
  template<typename Iterator>
  void add_word(Iterator first, Iterator last) {
    int cur = 0, len = 1;
    for(; first != last; ++first) {
      auto ch = AhoType::f(*first);
      if(tr[cur].nxt[ch] == 0) {
        tr[cur].nxt[ch] = int(tr.size());
        tr.emplace_back(cur, ch, len);
      }
      cur = tr[cur].nxt[ch];
      ++len;
    }
    tr[cur].occ_link = cur;
  }
  void build() {
    vector<int> bfs(int(tr.size()));
    int s = 0, t = 1;
    while(s < t) {
      int v = bfs[s++], u = tr[v].link;
      if(tr[v].occ_link == 0) {
        tr[v].occ_link = tr[u].occ_link;
      }
      for(int ch = 0; ch < AhoType::ALPHA; ++ch) {
        auto& nxt = tr[v].nxt[ch];
        if(nxt == 0) {
          nxt = tr[u].nxt[ch];
        } else {
          tr[nxt].link = v > 0 ? tr[u].nxt[ch] : 0;
          bfs[t++] = nxt;
        }
      }
    }
  }
  template<typename Iterator, typename Report>
  void get_all_matches(Iterator first, Iterator last, Report&& report) const {
    for(int cur = 0, i = 0; first != last; ++i, ++first) {
      auto ch = AhoType::f(*first);
      cur = tr[cur].nxt[ch];
      for(int v = tr[cur].occ_link; v > 0; v = tr[tr[v].link].occ_link) {
        report(i, v);
      }
    }
  }
  template<typename T>
  int get_next(int cur, T ch) const { return tr[cur].nxt[AhoType::f(ch)]; }
};
