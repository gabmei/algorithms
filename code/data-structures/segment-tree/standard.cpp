struct Node{
	long long x; //atributes
	Node():x(0){} //empty constructor
	Node(long long _x):x(_x){} // init
	Node operator+(const Node& o){ // merge function
		
	}
};
//T: internal type
//F: external type
template<class T, class F>
struct SegmentTree{
public:
	SegmentTree(int _n=0):n(_n),tree(4*n){}
	void build(const vector<F>& arr){
		build(1, 0, n-1, arr);
	}
	void update(int x, F val){
		update(1, 0, n-1, x, T(val));
	}
	T query(int l, int r){
		T cur;
		query(1, 0, n-1, l, r, cur);
		return cur;
	}
private:
	int n;
	vector<T>tree;
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
	void update(int pos, int tl, int tr, int x, const T& val){
		if(tl==tr){
			tree[pos] = val;
		}else{
			int mid = (tl + tr)/2, esq = 2 * pos, dir = esq + 1;
			if(x<=mid) update(esq, tl, mid, x, val);
			else update(dir, mid+1, tr, x, val);
	
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
			query(esq, tl, mid, l, r, cur);
			query(dir, mid+1, tr, l, r, cur);
		}
	}
};
