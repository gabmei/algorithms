void countsort(vector<int>& sa, const vector<int>& c){
    int n = (int)sa.size();
    vector<int> cnt(n + 1), sa_new(n);
    for(int x : c) ++cnt[x + 1];
    for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
    for(int x : sa) sa_new[cnt[c[x]]++] = x;
    sa.swap(sa_new);
}
template<class T>
vector<int> suffixArray(const T& s){
    int n = (int)s.size();
    auto mod = [&n](int x){ return x < 0 ? x + n : x >= n ? x - n : x; };
    vector<int> sa(n), c(n);
    iota(begin(sa), end(sa), 0);//sa[i] = i
    sort(begin(sa), end(sa), [&](int a, int b){ return s[a] < s[b]; });
    int m = 0;
    c[sa[0]] = m++;
    for(int i = 1; i < n; ++i) c[sa[i]] = s[sa[i]] != s[sa[i - 1]] ? m++ : m - 1;
    for(int h = 1; h < n && m < n; h <<= 1){
        for(int& x : sa)x = mod(x - h);
            countsort(sa, c);
            vector<int>c_new(n);
            m = 0;
            c_new[sa[0]] = m++;
            for(int i = 1; i < n; ++i){
                pair<int,int> prev = {c[sa[i - 1]], c[mod(sa[i - 1] + h)]};
                pair<int,int> cur = {c[sa[i]],c[mod(sa[i] + h)]};
                c_new[sa[i]] = prev != cur ? m++ : m - 1;
            }
        c.swap(c_new);
    }
    return sa;
}

template<class T>
vector<int> getLCP(const T& s, const vector<int>& sa){
    int n = (int)s.size();
    vector<int> lcp(n), inv(n);
    for(int i = 0; i < n; ++i) inv[sa[i]] = i;
    for(int i = 0, k = 0; i < n - 1; ++i, k = k > 0 ? k - 1 : 0){
        int j = sa[inv[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
            lcp[inv[i]] = k;
        }
    return lcp;
}
