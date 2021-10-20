template<class T>
struct BIT{
    int n;
    vector<T>bit;
    BIT(int n_=0):n(n_),bit(n+1){} //1-based
    void update(int x, T val){
        for(;x<=n;x+=(x&-x))bit[x]+=val;
    }
    T query(int x){ //query on [1,r]
        T ret=0;
        for(;x>0;x-=(x&-x))ret+=bit[x];
        return ret;
    }
    T query(int l, int r){ //query on [l,r]
        if(l==r){
            T ret=bit[r--];
            for(l-=(l&-l);l!=r;r-=(r&-r)){
                ret-=bit[r];
            }
            return ret;
        }else{
            return query(r)-query(l-1);
        }
    }
    int lower_bound(T sum){ // first pos such that sum [1, pos] >= sum
        int pos=0;
        for(int pw=(1<<25);pw>0;pw>>=1){
            if(pos+pw<=n && bit[pos+pw]<sum){
                sum-=bit[pos+pw];
                pos+=pw;
            }
        }
        return pos+1;
    }
};
