template<typename T>
void reorder_polygon(vector<Point<T>>& P){
  size_t pos = 0;
  for(size_t i = 1; i < P.size(); i++){
    if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) {
      pos = i;
    }
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}
// points ordered ccw
template<typename T>
vector<Point<T>> minkowski(vector<Point<T>> P, vector<Point<T>> Q){
  // the first vertex must be the lowest
  reorder_polygon(P);
  reorder_polygon(Q);
  // we must ensure cyclic indexing
  P.push_back(P[0]);
  P.push_back(P[1]);
  Q.push_back(Q[0]);
  Q.push_back(Q[1]);
  // main part
  vector<Point<T>> result;
  for(size_t i = 0, j = 0; i < P.size() - 2 || j < Q.size() - 2; ){
    result.push_back(P[i] + Q[j]);
    auto c = cross(P[i + 1] - P[i], Q[j + 1] - Q[j]);
    if(c >= 0 && i < P.size() - 2) {
      ++i;
    }
    if(c <= 0 && j < Q.size() - 2) {
      ++j;
    }
  }
  return result;
}
