const int mod=1e9+7;
struct MB{
    int x;
    MB(int _x=0):x(_x){}
    void operator +=(const MB& o){ *this = *this + o; }
    void operator -=(const MB& o){ *this = *this - o; }
    void operator *=(const MB& o){ *this = *this * o; }
    MB& operator ++(){ return *this = *this + MB(1); }
    MB operator ++(int){ MB r=*this; ++(*this); return r; }
    MB operator +(const MB& o){ return x+o.x >=mod ? x+o.x-mod : x+o.x; }
    MB operator -(const MB& o){ return x-o.x < 0 ? x-o.x+mod : x-o.x; }
    MB operator *(const MB& o){ return int(1ll*x*o.x%mod); }
    operator int(){return x;}
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
struct Binomial{
    vector<MB>fat,invFat,inv;
    Binomial(int n):fat(n,1),invFat(n,1),inv(n,0){
        inv[1] = 1;
        for(int i=2;i<n;++i){
            fat[i] = MB(i)*fat[i-1];
            inv[i] = MB(0) - MB(mod/i)*inv[mod%i]; 
            invFat[i] = invFat[i-1]*inv[i];
        }
    }
    // n choose k
    MB operator() (int n, int k){
        return fat[n]*invFat[k]*invFat[n-k];
    }
};
