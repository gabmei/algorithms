struct TrieType {
  static const int ALPHA = 26;
  static int f(char c) { return c - 'a'; }
};
template<typename TrieType>
struct Trie {
  static const TrieType T;
  struct Node {
    int nxt[T.ALPHA] {};
    int cnt = 0;
    bool terminal = false;
  };
  vector<Node> tr;
  Trie() : tr(1) {}
  template<typename Iterator>
  void add_word(Iterator first, Iterator last) {
    int cur = 0;
    for(; first != last; ++first) {
      auto ch = T.f(*first);
      if(tr[cur].nxt[ch] == 0) {
        tr[cur].nxt[ch] = int(tr.size());
        tr.emplace_back();
      }
      tr[cur].cnt += 1;
      cur = tr[cur].nxt[ch];
    }
    tr[cur].cnt += 1;
    tr[cur].terminal = true;
  }
};
