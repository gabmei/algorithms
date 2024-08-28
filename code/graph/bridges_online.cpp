int par[MAXN], sz[MAXN], ds[MAXN], twcc[MAXN], mark[MAXN], upd_twcc[MAXN], mark_cnt, bridges;
void init(int n) {
  iota(ds, ds + n, 0);
  iota(twcc, twcc + n, 0);
  fill(sz, sz + n, 1);
  fill(par, par + n, -1);
}
int ds_root(int x) { return ds[x] == x ? x : ds[x] = ds_root(ds[x]); }
int twcc_root(int x) { return twcc[x] == x ? x : twcc[x] = twcc_root(twcc[x]); }
void rootify(int u) {
  mark_cnt++;
  int root = u, lst = -1;
  while(u != -1) {
    if(mark[twcc_root(u)] != mark_cnt) {
      mark[twcc_root(u)] = mark_cnt;
      upd_twcc[twcc_root(u)] = u;
    }
    if(twcc_root(u) == u) {
      twcc[upd_twcc[u]] = upd_twcc[u];
      twcc[u] = upd_twcc[u];
    }
    int nxt = par[u];
    par[u] = lst;
    ds[u] = root;
    lst = u;
    u = nxt;
  };
  sz[root] = sz[lst];
}
void unite_comp(int a, int b) {
  int ca = ds_root(a), cb = ds_root(b);
  if(sz[ca] < sz[cb]) {
    swap(ca, cb);
    swap(a, b);
  }
  rootify(b);
  par[b] = ds[b] = a;
  sz[ca] += sz[b];
}
bool check_lca(int x, vector<int>& px) {
  if(x != -1) {
    px.emplace_back(x);
    if(mark[x] == mark_cnt) {
      return true;
    }
    mark[x] = mark_cnt;
  }
  return false;
}
void remove_bridges(int lca, vector<int>& px) {
  for(auto x : px) {
    twcc[x] = lca;
    if(x == lca) break;
    --bridges;
  }
}
void unite_path(int a, int b) {
  mark_cnt++;
  a = twcc_root(a), b = twcc_root(b);
  vector<int> pa, pb;
  int lca = -1;
  while(lca == -1) {
    if(a != -1) {
      pa.emplace_back(a);
      if(mark[a] == mark_cnt) {
        lca = a;
        break;
      }
      mark[a] = mark_cnt;
      a = par[a] == -1 ? -1 : twcc_root(par[a]);
    }
    if(b != -1) {
      pb.emplace_back(b);
      if(mark[b] == mark_cnt) {
        lca = b;
        break;
      }
      mark[b] = mark_cnt;
      b = par[b] == -1 ? -1 : twcc_root(par[b]);
    }
  }
  remove_bridges(lca, pa);
  remove_bridges(lca, pb);
}
void add_edge(int a, int b) {
  if(ds_root(a) != ds_root(b)) {
    ++bridges;
    unite_comp(a, b);
  } else if(twcc_root(a) != twcc_root(b)) {
    unite_path(a, b);
  }
}
