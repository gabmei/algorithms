struct Node{
    int x; //atributes
    Node():x(0){} //empty constructor
    Node(int _x):x(_x){} // init
    Node& operator+=(const Node& rhs){ // merge function
        /* addition of rhs to *this here */
        return *this;
    }
    friend Node operator+(Node lhs, const Node& rhs){ return lhs += rhs; }
};

template<class T>
struct SegmentTree{
public:
	SegmentTree(int _n=0):n(_n),tree(4*n, T()){}
	SegmentTree(const vector<T>& arr):n((int)arr.size()),tree(4*n, T()){
		build(1, 0, n, arr);
	}
	void update(int x, T val){
		update(1, 0, n, x, val);
	}
	T query(int l, int r){
		T cur = T(); 
		query(1, 0, n, l, r, cur);
		return cur;
	}
private:
	int n;
	vector<T>tree;
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
	void update(int p, int tl, int tr, int x, const T& val){
		if(tl + 1 == tr){
			tree[p] = val;
		}else{
			int mid = (tl + tr)/2;
			if(x<mid) update(left(p), tl, mid, x, val);
			else update(right(p), mid, tr, x, val);
	
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
			query(left(p), tl, mid, l, r, cur);
			query(right(p), mid, tr, l, r, cur);
		}
	}
};
