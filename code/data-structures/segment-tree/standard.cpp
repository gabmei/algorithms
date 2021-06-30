struct node{
	int x;
	node(int _x=0):x(_x){}
	node operator+(const node &o){ // merge function
		return node(x^o.x);
	}
}nil(0);
struct SegmentTree{
	int n;
	vector<node>tree;
	SegmentTree(int _n=0):n(_n),tree(4*n,nil){}
	void build(int pos,int tl,int tr,const vector<node> &arr){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos]=arr[tl];
		}else{
			build(esq,tl,mid,arr);
			build(dir,mid+1,tr,arr);
 
			tree[pos]=tree[esq]+tree[dir];
		}
	}
	void build(const vector<node> &arr){
		build(1,0,n-1,arr);
	}
	
	void update(int pos,int tl,int tr,int x, node val){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos]=tree[pos]+val;//assign update
		}else{
			if(x<=mid)update(esq,tl,mid,x,val);
			else update(dir,mid+1,tr,x,val);
	 
			tree[pos]=tree[esq]+tree[dir];
		}
	}
 
	void update(int x, node val){
		update(1,0,n-1,x,val);
	}
 
	node query(int pos, int tl, int tr, int l, int r){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
	 
		if(tl>r || tr<l){
			return nil;//depends of the query type
		}else if(tl>=l && tr<=r){
			return tree[pos];
		}else{
			return query(esq,tl,mid,l,r)+query(dir,mid+1,tr,l,r);
		}
	}
	node query(int l, int r){
		return query(1,0,n-1,l,r);
	}
};
