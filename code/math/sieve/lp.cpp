const int ms = 5e5 + 10;
int lp[ms]; // lp[i]: lowest prime of i
vector<int> pr;
void sieve(){
    for(int i = 2; i < ms; ++i){
        if(lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
        }
        for(int p : pr){
            if(p > lp[i] || i * p >= ms)break;
            lp[i * p] = p;
        }
    }
}
template<class T>
void getPrimes(int x, T&& get){
    while(x != 1){
        int p = lp[x];
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
vector<int> getMasks(int x){
    vector<int>masks({1});
    while(x != 1){
        getPrimes(x, [&x,&masks](int p, int e){
            int n = (int)masks.size();
            for(int i = 0; i < n; ++i){
                int u = masks[i];
                masks.emplace_back(u * p);
            }   
            for(int j = 0; j < e; ++j)x /= p;
        });
    }
    return masks;
}
