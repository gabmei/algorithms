struct node{
    int r,b;
    node(int r=0,int b=0):r(r),b(b){}
}nil(0,0);
struct SegmentTree{
	vector<node>tree;
	int n;
	SegmentTree(int n):n(n),tree(4*n,nil){}
	node combine(const node& a,const node& b){ //merge function
		return node(a.r+b.r,a.b+b.b);
	}
	void build(int pos,int tl,int tr,const vector<node> &arr){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos]=arr[tl];
		}else{
			build(esq,tl,mid,arr);
			build(dir,mid+1,tr,arr);
 
			tree[pos]=combine(tree[esq],tree[dir]);
		}
	}
	void build(const vector<node> &arr){
		build(1,0,n-1,arr);
	}
	
	void update(int pos,int tl,int tr,int x, node val){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
		if(tl==tr){
			tree[pos]=val;//assign update
		}else{
			if(x<=mid)update(esq,tl,mid,x,val);
			else update(dir,mid+1,tr,x,val);
	 
			tree[pos]=combine(tree[esq],tree[dir]);
		}
	}
 
	void update(int x, node val){
		update(1,0,n-1,x,val);
	}
 
	node query(int pos, int tl, int tr, int l, int r){
		int esq=2*pos, dir=2*pos+1;
		int mid = (tl+tr)/2;
	 
		if(r<tl || l>tr){
			return nil;//depends of the query type
		}else if(tl>=l && tr<=r){
			return tree[pos];
		}else{
			return combine(query(esq,tl,mid,l,r), query(dir,mid+1,tr,l,r));
		}
	}
	node query(int l, int r){
		return query(1,0,n-1,l,r);
	}
};
