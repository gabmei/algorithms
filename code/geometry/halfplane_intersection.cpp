using ld = long double;
using DT = Double<ld>;
using PT = Point<DT>;
using LI = Line<DT>;
const DT INF = 1e18;
vector<PT> halfplane_intersection(vector<LI> line) {
  vector<PT> box{PT(INF, INF), PT(-INF, INF), PT(-INF, -INF), PT(INF, -INF)};
  for(int i = 0; i < 4; ++i) { // Add bounding box half-planes.
    line.emplace_back(box[i], box[(i + 1) % 4] - box[i]);
  }
  // Sort by angle and start algorithm
  sort(begin(line), end(line), [&](LI u, LI v) {
    return polar_cmp(u.d, v.d);
  });
  auto outside_halfplane = [&](LI hp, PT p) {
    return clockwise(hp.d, p - hp.A);
  };
  auto is_redundant = [&](LI a, LI b, LI c) {
    return outside_halfplane(a, line_intersection(b, c));
  };
  deque<LI> hp;
  int len = 0;
  for(int i = 0, n = (int)line.size(); i < n; ++i) {
    // Remove from the back of the deque while last half-plane is redundant
    while(len > 1 && is_redundant(line[i], hp[len - 1], hp[len - 2])) {
      hp.pop_back();
      --len;
    }
    // Remove from the front of the deque while first half-plane is redundant
    while(len > 1 && is_redundant(line[i], hp[0], hp[1])) {
      hp.pop_front();
      --len;
    }
    // Special case check: Parallel half-planes
    if(len > 0 && cross(line[i].d, hp[len - 1].d) == DT(0)) {
      // Opposite parallel half-planes that ended up checked against each other.
      if(dot(line[i].d, hp[len - 1].d) < DT(0)) {
        return vector<PT>();
      }
      // Same direction half-plane: keep only the leftmost half-plane.
      if(outside_halfplane(line[i], hp[len - 1].A)) {
        hp.pop_back();
        --len;
      } else continue;
    }
    // Add new half-plane
    hp.push_back(line[i]);
    ++len;
  }
  // Final cleanup: Check half-planes at the front against the back and vice-versa
  while(len > 2 && is_redundant(hp[0], hp[len - 1], hp[len - 2])) {
    hp.pop_back();
    --len;
  }
  while(len > 2 && is_redundant(hp[len - 1], hp[0], hp[1])) {
    hp.pop_front();
    --len;
  }
  // Report empty intersection if necessary
  if (len < 3) {
    return vector<PT>();
  }
  // Reconstruct the convex polygon from the remaining half-planes.
  vector<PT> inter(len);
  for(int i = 0; i < len; ++i) {
    int j = i + 1 == len ? 0 : i + 1;
    inter[i] = line_intersection(hp[i], hp[j]);
  }
  return inter;
}
