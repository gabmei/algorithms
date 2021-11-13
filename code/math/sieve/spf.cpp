const int ms = 1e6 + 50;
int spf[ms]; // spf[i] = smallest prime factor of i
void sieve(){
    iota(spf, spf + ms, 0); // spf[i] = i
    for(int i = 2; i < ms; ++i){
        if(spf[i] != i || 1ll * i * i > ms) continue;
        for(int j = i * i; j < ms; j += i){
            if(spf[j] == j)spf[j] = i;
        }
    }
}
template<class T>
void getPrimes(int x, T&& get){
    while(x != 1){
        int p = spf[x];
        int e = 0;
        while(x%p==0){
            x/=p;
            ++e;
        }
        get(p, e);
    }
}
vector<int> getDivisors(int x){
    vector<int>divisors({1});
    while(x != 1){
        getPrimes(x, [&x,&divisors](int p, int e){
            int n = (int)divisors.size();
            for(int i = 0; i < n; ++i){
                int u = divisors[i];
                for(int j = 0, v = p; j < e; ++j, v *= p){
                    divisors.emplace_back(u * v);
                }
            }   
            for(int j = 0; j < e; ++j)x /= p;
        });
    }
    return divisors;
}
