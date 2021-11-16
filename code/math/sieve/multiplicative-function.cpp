template<class T>
struct MultiplicativeFunction{
    vector<T> ans;
    vector<bool> pr;
    //Dirichlet == true: unit function (ans[1] = 1, ans[i] = 0)
    //Dirichlet == false: constant function (ans[i] = 1)
    MultiplicativeFunction(int n, bool Dirichlet = true):ans(n){
        if(Dirichlet) ans[1] = 1;
        else fill(begin(ans),end(ans),1);
    }
    //f: evaluates the multiplicative function at a prime power
    template<class F>
    MultiplicativeFunction(int n, F&& f):ans(n, 1), pr(n, 1){
        pr[1] = false;
        for(int i = 2; i < n; ++i){
            if(!pr[i]) continue;
            ans[i] = f(i, 1);
            for(int u = i, e = 2; u < n / i; u *= i, ++e){
                ans[u * i] = f(i, e);
            }
            for(int j = i + i; j < n; j += i){
                int x = j;
                while(x % i == 0) x /= i;
                ans[j] = ans[x] * ans[j / x]; // multiplicative property: (x, j / x) = 1 
                pr[j] = false;
            }
        }
    }
    using MF = MultiplicativeFunction<T>;
    // Dirichlet convolution
    // f * g [n] = sum of f[d] * g[n/d]
    MF& operator*=(const MF& rhs){
        int n = (int)ans.size();
        vector<T> r(n);
        for(int i = 1; i < n; ++i)
            for(int j = i; j < n; j += i)
                r[j] += ans[i] * rhs[j / i];
        ans.swap(r);
        return *this;
    }
    friend MF operator*(MF lhs, const MF& rhs){ return lhs *= rhs; }
    const T& operator[](int i) const { return ans[i]; }
};
template<class T>
using MF = MultiplicativeFunction<T>;

template<class T>
MF<T> binExp(MF<T> a, long long e){
    int n = (int)a.ans.size();
    MF<T> r(n, true);
    for(; e > 0; e >>= 1){
        if(e & 1) r *= a;
        a *= a;
    }
    return r;
}

// Mobius function
template<class T>
struct Mobius : MF<T> {
    using MF<T>::MF;
    using MF<T>::operator=;
    Mobius(int n):MF<T>(n, [](int, int e){
        return e > 1 ? 0 : -1;
    }){};
};

// Euler's totient
template<class T>
struct PHI : MF<T> {
    using MF<T>::MF;
    using MF<T>::operator=;
    PHI(int n):MF<T>(n, [](int p, int e){
        T pw = 1;
        for(int j = 0; j < e - 1; ++j) pw *= p;
        return pw * (p - 1);
    }){};
};

// Number of divisors
template<class T>
struct NUMDIV : MF<T> {
    using MF<T>::MF;
    using MF<T>::operator=;
    NUMDIV(int n):MF<T>(n, [](int, int e){
        return e + 1;
    }){};
};

// Sum of divisors
template<class T>
struct SUMDIV : MF<T> {
    using MF<T>::MF;
    using MF<T>::operator=;
    SUMDIV(int n):MF<T>(n, [](int p, int e){
        T pw = 1;
        for(int j = 0; j < e + 1; ++j) pw *= p;
        return (pw - 1) / (p - 1);
    }){};
};
