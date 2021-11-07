template<class F = unsigned int, class T = string>
struct RabinKarp{
    int n;
    vector< F > p, pw;
    static constexpr F C[2] = {727, 137};
    RabinKarp(){}
    //change C id for double hashing
    RabinKarp(const T& s, bool id):n((int)s.size()),p(n+1),pw(n+1,1){
        for(int i=1;i<=n;i++){
            pw[i] = pw[i-1]*C[id];
            p[i] = p[i-1]*C[id] + s[i-1];
        }
    }
    F hash(int i, int len){return p[i+len] - pw[len]*p[i];}
};
