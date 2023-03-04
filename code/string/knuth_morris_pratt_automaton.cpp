#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct KMP {
  int id(char x) {return x - 'a';}
  int n,sigma;
  vector<vector<int>> aut;
  KMP(const T& pat, int _sigma=26) {
    n = (int)pat.size();
    sigma = _sigma;
    aut.assign(n + 1, vector<int>(sigma));
    aut[0][id(pat[0])] = 1;
    for(int i = 1, j = 0; i <= n; ++i) {
      copy(aut[j].begin(), aut[j].end(), aut[i].begin());
      if(i < n) {
        int c = id(pat[i]);
        aut[i][c] = i + 1;
        j = aut[j][c];
      }
    }
  }
  template<typename F>
  void match_pattern(const T& txt, F get) {
    int m = (int)txt.size();
    for(int i = 0, j = 0; i < m; ++i) {
      j = aut[j][id(txt[i])];
      if(j == n) {
        get(i - n + 1);
      }
    }
  }
};