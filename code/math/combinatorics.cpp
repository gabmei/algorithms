template<class T>
struct Combinatorics{
    vector<T> fat, inv, pref, suf;
    Combinatorics(int n):fat(n),inv(n),pref(n),suf(n){
        fat[0] = inv[0] = 1;
        for(int i = 1; i < n; ++i){
            fat[i] = T(i) * fat[i - 1];
            inv[i] = T(1) / fat[i];
        }
    }
    
    // n choose k
    T choose(int n, int k){
        return k < 0 || n < k ? T(0) : fat[n] * inv[k] * inv[n - k];
    }

    // n stars and k bars
    T bars(int n, int k){
        return choose(n + k - 1, k - 1);
    }
    
    // interpolate points (i, y[i]) and evaluate at x
    T interpolate(const vector<T>& y, T x){
        int n = (int)y.size();
        pref[0] = suf[n - 1] = 1;
        for(int i = 0; i + 1 < n; ++i) pref[i + 1] = pref[i] * T(x - i);
        for(int i = n - 1; i > 0; --i) suf[i - 1] = suf[i] * T(x - i);

        T ans = 0;
        // beware negative sgn
        for(int i = 0, sgn = (n % 2 ? +1 : -1); i < n; ++i, sgn *= -1){
            ans += T(sgn) * y[i] * pref[i] * suf[i] * inv[i] * inv[n - 1 - i];
        }
        return ans;
    }
};
