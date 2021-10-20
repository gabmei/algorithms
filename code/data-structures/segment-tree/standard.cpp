struct Node{
	long long x; //atributes
	Node():x(0){} //empty constructor
	Node(long long _x):x(_x){} // init
	Node operator+(const Node &o){ // merge function
		return Node(max(x,o.x));
	}
};
//T: internal type
//F: external type
template<class T, class F>
struct SegmentTree{
	int n;
	vector<T>tree;
	SegmentTree(int _n=0):n(_n),tree(4*n){}
	void build(int pos,int tl,int tr,const vector<F> &arr){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos] = T(arr[tl]);
		}else{
			build(esq,tl,mid,arr);
			build(dir,mid+1,tr,arr);
 
			tree[pos] = tree[esq] + tree[dir];
		}
	}
	void build(const vector<F> &arr){
		build(1,0,n-1,arr);
	}
	void update(int pos,int tl,int tr,int x, T val){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos] = val;
		}else{
			if(x<=mid)update(esq,tl,mid,x,val);
			else update(dir,mid+1,tr,x,val);
	 
			tree[pos] = tree[esq] + tree[dir];
		}
	}
 
	void update(int x, F val){
		update(1,0,n-1,x,T(val));
	}
 
	T query(int pos, int tl, int tr, int l, int r){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
	 
		if(tl>r || tr<l){
			return T(); 
		}else if(tl>=l && tr<=r){
			return tree[pos];
		}else{
			return query(esq,tl,mid,l,r) + query(dir,mid+1,tr,l,r);
		}
	}
	T query(int l, int r){
		return query(1,0,n-1,l,r);
	}
};
