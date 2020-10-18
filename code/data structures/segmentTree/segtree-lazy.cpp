//range assign update, range sum query

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
	ll x;
	node(ll x):x(x){}
	bool operator == (node o) {return x==o.x;}
	bool operator != (node o) {return x!=o.x;}
}nil(0);

vector<node>tree;
vector<node>lazy;

void init_(int n){
	tree.assign(4*(n+1),nil);
	lazy.assign(4*(n+1),nil);
}

node combine(const node& a,const node& b){
	return node(a.x+b.x);
}

void calc(node& a, const node& b, ll len){
    a= node(b.x*len);
}

void push(int pos, int tl,int tr){
	if(lazy[pos]!=nil){
		int esq=2*pos, dir=2*pos+1;
        int mid = (tl+tr)/2;
		calc(tree[esq],lazy[pos],mid-tl+1);
        calc(tree[dir],lazy[pos],tr-(mid+1)+1);

		lazy[esq]=lazy[dir]=lazy[pos];
		lazy[pos]=nil;
	}
}

void update(int pos, int tl, int tr, int l, int r, node val){
	int esq=2*pos, dir=2*pos+1;
	int mid = (tl+tr)/2;	
	
	if(tl>r ||tr<l){
		return;
	}else if(tl>=l && tr<=r){
		calc(tree[pos],val,tr-tl+1);
		lazy[pos]=val;
	}else{
		push(pos,tl,tr);
		update(esq,tl,mid,l,r,val);
		update(dir,mid+1,tr,l,r,val);

		tree[pos]=combine(tree[esq],tree[dir]);
	}
	
}
node query(int pos, int tl, int tr, int l, int r){
	int esq=2*pos, dir=2*pos+1;
	int mid = (tl+tr)/2;

	if(tl>r ||tr<l){
		return nil;
	}else if(tl>=l && tr<=r){
		return tree[pos];
	}else{
		push(pos,tl,tr);
		auto left=query(esq,tl,mid,l,r),right=query(dir,mid+1,tr,l,r);
		return combine(left,right);
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n,m;
	cin>>n>>m;
	init_(n);
	while(m--){
		int op;
		cin>>op;
		if(op==1){
			int l,r,v;
			cin>>l>>r>>v;
			update(1,0,n-1,l,r-1,node(v));
		}else{
			int l,r;
			cin>>l>>r;
			ll ans = query(1,0,n-1,l,r-1).x;
			cout<<ans<<'\n';
		}
	}

	return 0;
}