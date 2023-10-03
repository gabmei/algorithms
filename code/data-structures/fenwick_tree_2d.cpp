template<typename T>
struct FenwickTree2D {
public:
  FenwickTree2D(const vector<pair<T, T>>& p) {
    for(auto [x, _] : p) {
      ord.push(x);
    }
    fw.resize(ord.build() + 1);
    coord.resize((int)fw.size());
    for(auto [x, y] : p) {
      for(int on = ord[x + 1]; on < (int)fw.size(); on += lsb(on)) {
        coord[on].push(y);
      }
    }
    for(int i = 0; i < (int)fw.size(); ++i) {
      fw[i].assign(coord[i].build() + 1, T());
    }
  }
  void update(T x, T y, T v) {
    for(int xx = ord[x + 1]; xx < (int)fw.size(); xx += lsb(xx)) {
      for(int yy = coord[xx][y + 1]; yy < (int)fw[xx].size(); yy += lsb(yy)) {
        fw[xx][yy] += v;
      }
    }
  }
  T query(T x, T y) {
    T ans{};
    for(int xx = ord[x]; xx > 0; xx -= lsb(xx)) {
      for(int yy = coord[xx][y]; yy > 0; yy -= lsb(yy)) {
        ans += fw[xx][yy];
      }
    }
    return ans;
  }
  T query(T x1, T y1, T x2, T y2) { // [x1, x2), [y1, y2)
    return query(x2, y2) - query(x2, y1) - query(x1, y2) + query(x1, y1);
  }
  void update(T x1, T y1, T x2, T y2, T v) {
    update(x1, y1, +v);
    update(x1, y2, -v);
    update(x2, y1, -v);
    update(x2, y2, +v);
  }
private:
  CoordinateCompression<T> ord;
  vector<CoordinateCompression<T>> coord;
  vector<vector<T>> fw;
  static int lsb(int b) { return b & -b; }
};
