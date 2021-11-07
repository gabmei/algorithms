const int MOD=1e9+7;
template<class T>
T binExp(T a, long long e){
    T r(1);
    for(;e;e>>=1){
        if(e&1)r = r * a;
        a = a * a;
    }
    return r;
}
struct MB{
    int x;
    constexpr MB(int _x=0):x(_x >= MOD ? _x - MOD : _x < 0 ? _x + MOD : _x){}
    MB& operator+=(const MB& rhs){
        x += rhs.x;
        if(x >= MOD) x -= MOD;
        return *this;
    }
    MB& operator-=(const MB& rhs){
        x -= rhs.x;
        if(x < 0) x += MOD;
        return *this; 
    }
    MB& operator*=(const MB& rhs){
        x = int(1ll * x * rhs.x % MOD);
        return *this;
    }
    MB& operator/=(const MB& rhs){
        return *this *= binExp(rhs, MOD - 2);
    }
    friend MB operator+(MB lhs, const MB& rhs){ return lhs += rhs; }
    friend MB operator-(MB lhs, const MB& rhs){ return lhs -= rhs; }
    friend MB operator*(MB lhs, const MB& rhs){ return lhs *= rhs; }
    friend MB operator/(MB lhs, const MB& rhs){ return lhs /= rhs; }

    MB operator-() const { return MB() - *this; }
    
    bool operator==(const MB& rhs) const { return x == rhs.x; }
    bool operator!=(const MB& rhs) const { return !(*this == rhs); }

    friend ostream& operator<< (ostream& os, MB o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
