// minimum cartesian tree
struct Node {
  int l, r, p;
  Node(int l = 0, int r = 0, int p = 0) : l(l), r(r), p(p) {}
};
for(int i = 0; i < n; ++i) {
  tree[i] = Node(-1, -1, i - 1);
  while(tree[i].p != -1 && h[tree[i].p] > h[i]) {
    tree[i].l = tree[i].p;
    tree[i].p = tree[tree[i].p].p;
  }
  if(tree[i].l != -1) tree[tree[i].l].p = i;
  if(tree[i].p != -1) tree[tree[i].p].r = i;
}
