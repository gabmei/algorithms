const int N = 2;
template<typename T>
struct Matrix {
  T a[N][N];
  Matrix(bool identity = false) {
    for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
        a[i][j] = T(0);
      }
      a[i][i] = T(identity);
    }
  }
  Matrix operator *(const Matrix& b) {
    Matrix p;
    for(int i = 0; i < N; ++i)
      for(int j = 0; j < N; ++j)
        for(int k = 0; k < N; ++k)
          p.a[i][k] += a[i][j] * b.a[j][k];
    return p;
  }
};
