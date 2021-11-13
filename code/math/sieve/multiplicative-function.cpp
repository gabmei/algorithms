//f: evaluates the multiplicative function at a prime power
template<class T, T (*f)(int, int)>
struct MultiplicativeFunction{
    vector<T> ans;
    vector<bool> pr;
    MultiplicativeFunction(int n):ans(n, 1), pr(n, true){
        for(int i = 2; i < n; ++i){
            if(!pr[i]) continue;
            
            for(int u = i, e = 1; true; u *= i, ++e){
                ans[u] = f(i, e);
                if(n / u / i == 0)break; //checks for overflow
            }

            for(int j = i + i; j < n; j += i){
                int x = j;
                while(x % i == 0) x /= i;
                ans[j] = ans[x] * ans[j / x]; // multiplicative function
                pr[j] = false;
            }
        }
    }
    const T& operator[](int i){ return ans[i]; }
};
template<class T>
T mobiusFunction(int p, int e){return e > 1 ? 0 : -1; }
template<class T>
using Mobius = MultiplicativeFunction<T,mobiusFunction<T>>;

template<class T>
T eulerTotient(int p, int e){
    T pw = 1;
    for(int j = 0; j < e - 1; ++j) pw *= p;
    return pw * (p - 1);
}
template<class T>
using PHI = MultiplicativeFunction<T, eulerTotient<T>>;

template<class T>
T numberOfDivisors(int, int e){ return e + 1; }
template<class T>
using NUMDIV = MultiplicativeFunction<T,numberOfDivisors<T>>;

template<class T>
T sumOfDivisors(int p, int e){
    T pw = 1;
    for(int j = 0; j < e + 1; ++j) pw *= p;
    return (pw - 1) / (p - 1);
}
template<class T>
using SUMDIV = MultiplicativeFunction<T,sumOfDivisors<T>>;
