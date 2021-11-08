template<class T, T (*f)(T, T)>
struct SparseTable{
    int n, k;
    vector<vector<T>> st;
    SparseTable(int _n):n(_n), k(__lg(n)){}
    SparseTable(const vector<T>& v):n(int(v.size())), k(__lg(n)){
        st.assign(k + 1, vector<T>(n));
        copy(begin(v),end(v),begin(st[0]));

        for(int j = 0; j < k; ++j)
            for(int i = 0; i + (1 << (j + 1)) <= n; ++i)
                st[j + 1][i] = f(st[j][i], st[j][i + (1 << j)]);
    }
    T query(int l, int r) const {
        int j = __lg(r - l);
        return f(st[j][l], st[j][r - (1 << j)]);
    }
};
template<class T>
static T minFunction(T a, T b){ return min(a,b); }
template<class T>
using RMQ = SparseTable<T, minFunction<T>>;