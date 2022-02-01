// T : input type
template<class T = string>
struct RabinKarp{
    int n;
    vector<MB> p[2], pw[2];
    static constexpr MB C[2] = {727, 137}; // double hashing
    RabinKarp(const T& s):n((int)s.size()){
        for(int e = 0; e < 2; ++e){
            p[e].assign(n + 1, 0);
            pw[e].assign(n + 1, 1);
            for(int i = 1; i <= n; ++i){
                pw[e][i] = pw[e][i - 1] * C[e];
                p[e][i] = p[e][i - 1] * C[e] + s[i - 1];
            }
        }
    }
    pair<int, int> hash(int i, int len){
        int h0 = (p[0][i + len] - pw[0][len] * p[0][i]).x;
        int h1 = (p[1][i + len] - pw[1][len] * p[1][i]).x;
        return {h0, h1};
    }
};
