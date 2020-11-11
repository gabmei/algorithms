struct node{
    	int x;
    	node(int x=0):x(x){}
	node operator+(const node& o){ // merge function
		return node(x+o.x);
	}
	bool operator!=(const node& o){
		return o.x != x;
	}
}nil(0),nada(-1);
 
struct SegmentTree{
	vector<node>tree,lazy;
	int n;
	SegmentTree(){}
	SegmentTree(int n):n(n),tree(4*n,nil),lazy(4*n,nada){}

	void calc(node& a, const node& b, int len){
		a= node(b.x*len);
	}
    
	void push(int pos, int tl,int tr){ //assignment update, sum query
		if(lazy[pos]!=nada){
			int esq=2*pos, dir=2*pos+1;
			int mid = (tl+tr)/2;
			calc(tree[esq],lazy[pos],mid-tl+1);
			calc(tree[dir],lazy[pos],tr-(mid+1)+1);
		
			lazy[esq]=lazy[dir]=lazy[pos];
			lazy[pos]=nil;
		}
	}
	void build(int pos,int tl,int tr, const vector<node>& arr){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos]=arr[tl];
		}else{
			build(esq,tl,mid,arr);
			build(dir,mid+1,tr,arr);
 
			tree[pos]=tree[esq] + tree[dir];
		}
	}
	void build(const vector<node>& arr){
		build(1,0,n-1,arr);
	}
	void update(int pos,int tl,int tr,int l, int r, node x){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl>r || tr<l){
			return;
		}else if(tl>=l && tr<=r){
			calc(tree[pos],x,tr-tl+1);
		    	lazy[pos]=x;
		}else{
			push(pos,tl,tr);
			update(esq,tl,mid,l,r,x);
			update(dir,mid+1,tr,l,r,x);
 
			tree[pos]=tree[esq]+tree[dir];
		}
	}
 
	void update(int l, int r, node x){
		update(1,0,n-1,l,r, x);
	}
	node query(int pos, int tl, int tr, int l, int r){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl>r || tr<l){
			return nil;//depends of the query type
		}else if(tl>=l && tr<=r){
			return tree[pos];
		}else{
			push(pos,tl,tr);
			return query(esq,tl,mid,l,r) + query(dir,mid+1,tr,l,r);
		}
	}
	node query(int l, int r){
		return query(1,0,n-1,l,r);
	}
};
