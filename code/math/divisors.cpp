template<class T>
void getDivisors(int x, T&& get){
    for(int i=1;i*i<=x;++i){
        if(x%i==0){
            get(i);
            if(x/i != i)get(x/i);
        }
    }
    return;
}
