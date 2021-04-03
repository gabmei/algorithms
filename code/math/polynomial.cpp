template<class T>
struct vec{
    int n;
    vector<T>v;
    vec(int _n,T val=0):n(_n),v(n,val){}
    void operator *=(const vec& o){ *this = *this * o; }
    vec operator *(const vec& o){
        vec r(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                r.v[(i+j)%n]+=v[i]*o.v[j];
            }
        }
        return r;
    }
    T& operator[](int i){ return v[i]; }
};
template<class T>
vec<T> binExp(vec<T> a,long long e){
    vec<T>r(a.n);r.v[0]=1;
    while(e){
        if(e&1)r*=a;
        a*=a;   
        e>>=1;
    }
    return r;
}
