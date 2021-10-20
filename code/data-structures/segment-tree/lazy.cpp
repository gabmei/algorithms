struct LazyContext{
	int x; //atributes
	LazyContext():x(-1){} //empty constructor
	LazyContext(int _x):x(_x){} // init
	void operator+=(const LazyContext& o){ // update Lazy
		
	}
	bool empty(){ return x == -1; }
	void reset(){ x = -1; }

};
struct Node{
	long long x; //atributes
	Node():x(0){} //empty constructor
	Node(long long _x):x(_x){} // init
	Node operator+(const Node& o){ // merge function
		
	}
	void apply(const LazyContext& lazy){ //update Node with Lazy
		
	}
};
//T: internal type
//F: external type
//L: Lazy type
template<class T, class F, class L>
struct SegmentTree{
public:
	SegmentTree(int _n=0):n(_n),tree(4*n),lazy(4*n){}
	void build(const vector<F>& arr){
		build(1, 0, n-1, arr);
	}
	void update(int l, int r, L val){
		update(1, 0, n-1, l, r, val);
	}
	T query(int l, int r){
		T cur;
		query(1, 0, n-1, l, r, cur);
		return cur;
	}
private:
	int n;
	vector<T>tree;
	vector<L>lazy;
	void build(int pos, int tl, int tr, const vector<F>& arr){
		if(tl == tr){
			tree[pos] = T(arr[tl]);
		}else{
			int mid = (tl + tr)/2, esq = 2 * pos, dir = esq + 1;
			build(esq, tl, mid, arr);
			build(dir, mid+1, tr, arr);

			tree[pos] = tree[esq] + tree[dir];
		}
	}
	void update(int pos, int tl, int tr, int l, int r, const L& val){
		if(tl>r || tr<l){
			return;
		}else if(tl>=l && tr<=r){
			tree[pos].apply(val);
			lazy[pos] += val;
		}else{
			int mid = (tl + tr)/2, esq = 2 * pos, dir = esq + 1;
			apply(pos);
			update(esq, tl, mid, l, r, val);
			update(dir, mid+1, tr, l, r, val);

			tree[pos] = tree[esq] + tree[dir];
		}
	}
	void query(int pos, int tl, int tr, int l, int r, T& cur){
		if(tl>r || tr<l){
			return;
		}else if(tl>=l && tr<=r){
			cur = cur + tree[pos];
		}else{
			int mid = (tl + tr)/2, esq = 2 * pos, dir = esq + 1;
			apply(pos);
			query(esq,tl,mid,l,r,cur);
			query(dir,mid+1,tr,l,r,cur);
		}
	}
	void apply(int pos){
		if(!lazy[pos].empty()){
			int esq = 2 * pos, dir = esq + 1;
			tree[esq].apply(lazy[pos]);
			tree[dir].apply(lazy[pos]);
			
			lazy[esq] += lazy[pos];
			lazy[dir] += lazy[pos];

			lazy[pos].reset();
		}
	}
};
