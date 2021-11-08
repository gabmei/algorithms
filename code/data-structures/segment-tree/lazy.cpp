struct LazyContext{
    int x; //atributes
    LazyContext():x(-1){} //empty constructor
    LazyContext(int _x):x(_x){} // init
    LazyContext& operator+=(const LazyContext& rhs){ // update Lazy
        /* addition of rhs to *this here */
        return *this;
    }
    bool empty(){ return x == -1; }
    void reset(){ x = -1; }
};
struct Node{
    int x; //atributes
    Node():x(0){} //empty constructor
    Node(int _x):x(_x){} // init
    Node& operator+=(const Node& rhs){ // merge function
        /* addition of rhs to *this here */
        return *this;
    }
    friend Node operator+(Node lhs, const Node& rhs){ return lhs += rhs; }
    void apply(const LazyContext& lazy){ //update Node with Lazy

    }
};
//T: Node type
//L: Lazy type
template<class T, class L>
struct SegmentTree{
public:
	SegmentTree(int _n=0):n(_n),tree(4*n, T()),lazy(4*n, L()){}
	SegmentTree(const vector<T>& arr):n((int)arr.size()),tree(4*n, T()),lazy(4*n, L()){
		build(1, 0, n, arr);
	}
	void update(int l, int r, L val){
		update(1, 0, n, l, r, val);
	}
	T query(int l, int r){
		T cur = T();
		query(1, 0, n, l, r, cur);
		return cur;
	}
private:
    int n;
    vector<T>tree;
    vector<L>lazy;
    static int left (int p){ return 2 * p; }
    static int right (int p){ return 2 * p + 1; }
    void build(int p, int tl, int tr, const vector<T>& arr){
        if(tl + 1 == tr){
            tree[p] = arr[tl];
        }else{
            int mid = (tl + tr)/2;
            build(left(p), tl, mid, arr);
            build(right(p), mid, tr, arr);

            tree[p] = tree[left(p)] + tree[right(p)];
        }
    }
    void update(int p, int tl, int tr, int l, int r, const L& val){
        if(tl>=r || tr<=l){
            return;
        }else if(tl>=l && tr<=r){
            tree[p].apply(val);
            lazy[p] += val;
        }else{
            int mid = (tl + tr)/2;
            apply(p);
            update(left(p), tl, mid, l, r, val);
            update(right(p), mid, tr, l, r, val);

            tree[p] = tree[left(p)] + tree[right(p)];
        }
    }
    void query(int p, int tl, int tr, int l, int r, T& cur){
        if(tl>=r || tr<=l){
            return;
        }else if(tl>=l && tr<=r){
            cur += tree[p];
        }else{
            int mid = (tl + tr)/2;
            apply(p);
            query(left(p), tl, mid, l, r, cur);
            query(right(p), mid, tr, l, r, cur);
        }
    }
    void apply(int p){
        if(!lazy[p].empty()){
            tree[left(p)].apply(lazy[p]);
            tree[right(p)].apply(lazy[p]);

            lazy[left(p)] += lazy[p];
            lazy[right(p)] += lazy[p];

            lazy[p].reset();
        }
    }
};