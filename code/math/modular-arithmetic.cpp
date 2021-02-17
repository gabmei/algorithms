const int mod=1e9+7;
template<class T>
T binExp(T a, long long e){
    T r=1;
    while(e){
        if(e&1)r*=a;
        a*=a;
        e>>=1;
    }
    return r;
}
struct MB{
    int x;
    MB(int x_=0):x(x_){}
    void operator +=(const MB& o){ *this = *this + o; }
    void operator -=(const MB& o){ *this = *this - o; }
    void operator *=(const MB& o){ *this = *this * o; }
    void operator /=(const MB& o){ *this = *this / o; }
    MB operator +(const MB& o){ return x+o.x >=mod ? x+o.x-mod : x+o.x; }
    MB operator -(const MB& o){ return x-o.x < 0 ? x-o.x+mod : x-o.x; }
    MB operator *(const MB& o){ return int(1ll*x*o.x%mod); }
    MB operator /(const MB& o){ return *this * binExp(o,mod-2); }
    operator int(){return x;}
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
