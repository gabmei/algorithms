template<int m>
struct MB{
    int x;
    MB(int x_=0):x(x_<0 ? x_+m : x_>=m ? x_-m : x_){}
    MB operator +(const MB& o){return x+o.x >=m ? x+o.x-m : x+o.x;}
    MB operator -(const MB& o){return x-o.x < 0 ? x-o.x+m : x-o.x;}
    MB operator *(const MB& o){return int(1ll*x*o.x%m);}
    operator int(){return x;}
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
 
const int mod1=1e9+7,mod2=1e9+9;
const MB base1=MB<mod1>(737);
const MB base2=MB<mod2>(3079);
struct RabinKarp{
    int n;
    vector< MB<mod1> > pref1,pow1;
    vector< MB<mod2> > pref2,pow2;
    RabinKarp(const string &s):n((int)s.size()),pref1(n+1),pow1(n+1,1),pref2(n+1),pow2(n+1,1){
        for(int i=1;i<=n;i++){
            pow1[i]=pow1[i-1]*base1;
            pow2[i]=pow2[i-1]*base2;
 
            pref1[i]=pref1[i-1]*base1 + MB<mod1>(s[i-1]);
            pref2[i]=pref2[i-1]*base2 + MB<mod2>(s[i-1]);
        }
    }
    MB<mod1> hash1(int i, int len){return pref1[i+len]-pow1[len]*pref1[i];}
    MB<mod2> hash2(int i, int len){return pref2[i+len]-pow2[len]*pref2[i];}
 
    bool equal(int i, int j, int len){
        return hash1(i,len)==hash1(j,len) && hash2(i,len)==hash2(j,len);
    }
 
};
