template<class T, class F = unsigned int>
struct RabinKarp{
    int n;
    vector< F > p, pw;
    //change C for double hashing
    RabinKarp(const T& s, const F C = 727):n((int)s.size()),p(n+1),pw(n+1,1){
        for(int i=1;i<=n;i++){
            pw[i] = pw[i-1]*C;
            p[i] = p[i-1]*C + s[i-1];
        }
    }
    F hash(int i, int len){return p[i+len] - pw[len]*p[i];}
};
