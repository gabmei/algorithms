template<class T>
struct BIT{
    static int lsb(int b){ return b & -b; }
    int n;
    vector<T>bit;
    BIT(int n_=0):n(n_),bit(n + 1, T()){}
    void update(int x, T val){
        for(++x; x <= n; x += lsb(x)) bit[x] += val;
    }
    T query(int x) const { //query on [0,x)
        T ret = T();
        for(; x > 0; x -= lsb(x))ret += bit[x];
        return ret;
    }
    T query(int l, int r) const { // query on [l,r)
        if(l + 1 == r){
            ++l;
            T ret=bit[r--];
            for(l -= lsb(l); l != r; r -= lsb(r)){
                ret-=bit[r];
            }
            return ret;
        }
        return query(r) - query(l);
    }
    // first pos such that value pred(query(0, pos + 1)) == false (n if no such value exists)
    template<class Pred>
    int find_right(Pred&& pred) const {
        T prefix = T();
        int pos = 0;
        for(int pw = (1 << 25); pw > 0; pw >>= 1){
            int npos = pos + pw;
            if(npos > n)continue;
            T nprefix = prefix + bit[npos];
            if(pred(nprefix)){
                pos = npos;
                prefix = nprefix;
            }
        }
        return pos;
    }

    int lower_bound(T value){ 
        return find_right([value](T x){ return x < value; });
    }
};
