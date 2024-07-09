template<typename T>
vector<int> get_border(const T& s) {
  int n = (int)s.size();
  vector<int> border(n);
  for(int i = 1, j = 0; i < n; ++i) {
    while(j > 0 && s[i] != s[j]) {
      j = border[j - 1];
    }
    if(s[i] == s[j]) {
      ++j;
    }
    border[i] = j;
  }
  return border;
}
template<typename T, typename F>
void match_pattern(const T& txt, const T& pat, const vector<int>& border, F get) {
  int n = (int)txt.size();
  int m = (int)pat.size();
  for(int i = 0, j = 0; i < n; ++i) {
    while(j > 0 && txt[i] != pat[j]) {
      j = border[j - 1];
    }
    if(txt[i] == pat[j]) {
      ++j;
    }
    if(j == m) {
      get(i - m + 1);
      j = border[j - 1];
    }
  }
}
