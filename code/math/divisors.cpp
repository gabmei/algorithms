template<class T, class F>
void getDivisors(T x, F&& get){
    for(T i = 1; i*i <= x; ++i){
        if(x%i==0){
            get(i);
            if(x/i != i)get(x/i);
        }
    }
    return;
}
void getPrimes(T x, F&& get){
    for(T i = 2; i*i <= x; ++i){
        if(x%i==0){
            while(x % i == 0)x /= i;
            get(i);
        }
    }
    if(x > 1)get(x);
    return;
}
