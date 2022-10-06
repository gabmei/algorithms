struct TwoSat {
  int N;
  std::vector<std::vector<int>> E;
  TwoSat(int N) : N(N), E(2 * N) {}
  int neg(int u) const {
    return (u + N) % (2 * N);
  }
  void add_or(int u, int v) {
    E[neg(u)].push_back(v);
    E[neg(v)].push_back(u);
  }
  void add_nand(int u, int v) {
    E[u].push_back(neg(v));
    E[v].push_back(neg(u));
  }
  void add_true(int u) {
    E[neg(u)].emplace_back(u);
  }
  void add_not(int u) {
    add_true(neg(u));
  }
  void add_xor(int u, int v) {
    add_or(u, v);
    add_nand(u, v);
  }
  void add_and(int u, int v) {
    add_true(u);
    add_true(v);
  }
  void add_nor(int u, int v) {
    add_and(neg(u), neg(v));
  }
  void add_xnor(int u, int v) {
    add_xor(u, neg(v));
  }
  // Assumes tarjan sorts SCCs in reverse topological order (u -> v implies scc[v] <= scc[u]).
  std::pair<bool, std::vector<bool>> solve() const {
    std::vector<bool> res(N);
    auto scc = tarjan(E);
    for (int u = 0; u < N; ++u) {
      if (scc[u] == scc[neg(u)]) return {false, {}};
      res[u] = scc[neg(u)] > scc[u];
    }
    return std::pair(true, res);
  }
};
