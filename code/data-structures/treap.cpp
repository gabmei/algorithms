const int seed = (int) std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);
struct Data {
  int pref, best, suf;
  Data(int pref = 0, int best = 0, int suf = 0) : pref(pref), best(best), suf(suf) {}
};
struct Node {
  bool val; 
  int prior, size;
  Node *l, *r;
  Data data[2];
  bool flip_lazy;
  Node() {}
  Node(bool val) : val(val), prior(uniform_int_distribution<>()(rng)), size(1), flip_lazy(false) {
    data[val] = Data(1, 1, 1);
    data[!val] = Data(0, 0, 0);
    l = r = nullptr;
  }
};

int size(Node* t) { return t ? t->size : 0; }
Data data(Node* t, int e) { return t ? t->data[e] : Data(0, 0, 0); }

void fix(Node* t) {
  if(!t) return;
  t->size = 1 + size(t->l) + size(t->r);
  for(int e = 0; e < 2; ++e) {
    auto ld = data(t->l, e);
    auto rd = data(t->r, e);
    t->data[e].pref = ld.pref;
    if(t->data[e].pref == size(t->l)) {
      t->data[e].pref += t->val == e ? 1 + rd.pref : 0;
    }
    t->data[e].suf = rd.suf;
    if(t->data[e].suf == size(t->r)) {
      t->data[e].suf += t->val == e ? 1 + ld.suf : 0;
    }
    t->data[e].best = max({ld.best, rd.best, t->data[e].pref, t->data[e].suf, t->val == e ? 1 + rd.pref + ld.suf : 0});
  }
}
void apply_flip(Node* t) {
  if(!t) return;
  t->val = !t->val;
  swap(t->data[0], t->data[1]);
}

void push(Node* t) {
  if(!t) return;
  if(!t->flip_lazy) return;
  if(t->l) {
    apply_flip(t->l);
    t->l->flip_lazy = !t->l->flip_lazy;
  }
  if(t->r) {
    apply_flip(t->r);
    t->r->flip_lazy = !t->r->flip_lazy;
  }
  t->flip_lazy = false;
}

pair<Node*, Node*> split(Node* t, int k) {
  if(!t) return {};
  push(t);
  if(size(t->l) >= k) {
    auto [L, R] = split(t->l, k);
    t->l = R; fix(t); return {L, t};
  } else {
    auto [L, R] = split(t->r, k - size(t->l) - 1);
    t->r = L; fix(t); return {t, R};
  }
}

Node* merge(Node* l, Node* r) {
  if(!l || !r) return l ? l : r;
  push(l); push(r);
  if(l->prior > r->prior) {
    l->r = merge(l->r, r);
    return fix(l), l;
  } else {
    r->l = merge(l, r->l);
    return fix(r), r;
  }
}

void update(Node* &t, int l, int r) {
  Node *left, *mid, *right;
  tie(mid, right) = split(t, r);
  tie(left, mid) = split(mid, l);
  if(mid) {
    apply_flip(mid);
    mid->flip_lazy = !mid->flip_lazy;
  }
  t = merge(merge(left, mid), right);
}

Node* root = nullptr;
for(int i = 0; i < N; ++i) {
  root = merge(root, new Node(str[i] == '1'));
}
// root <- informacao de todo o array
