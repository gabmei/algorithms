// F : modular type
// T : input type
template<class F = unsigned int, class T = string>
struct RabinKarp{
    int n;
    vector< F > p[2], pw[2];
    static constexpr F C[2] = {727, 137}; // double hashing
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
    pair<F, F> hash(int i, int len){
        return {p[0][i + len] - pw[0][len] * p[0][i], p[1][i + len] - pw[1][len] * p[1][i]};
    }
};
