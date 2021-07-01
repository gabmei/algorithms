template<int M>
struct MB{
    int x;
    MB(int _x=0):x(_x<0 ? _x+M : _x>=M ? _x-M : _x){}
    MB operator +(const MB& o){return {x+o.x >=M ? x+o.x-M : x+o.x};}
    MB operator -(const MB& o){return {x-o.x < 0 ? x-o.x+M : x-o.x};}
    MB operator *(const MB& o){return int(1ll*x*o.x%M);}
    explicit operator int(){return x;}
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
const int M1 = 1e9+7, M2 = 1e9+9;
const int C = 737;
template<class T>
struct RabinKarp{
    int n;
    vector< T > p,pw;
    RabinKarp(const string& s):n((int)s.size()),p(n+1),pw(n+1,1){
        for(int i=1;i<=n;i++){
            pw[i] = pw[i-1]*C;
            p[i] = p[i-1]*C + s[i-1];
        }
    }
    T hash(int i, int len){return p[i+len] - pw[len]*p[i];}
};
