#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
	ll sum;
	node(ll sum):sum(sum){};
}nil(0ll);

vector<node>tree;
vector<int>arr;

void init_(int n){
	tree.assign(4*(n+2),nil);
	arr.assign(n,0);
}

node combine(const node& a,const node& b){
	return node(a.sum+b.sum);
}
void build(int pos, int tl, int tr){
	int esq=2*pos, dir=2*pos+1;
	int mid = (tl+tr)/2;

	if(tl==tr){
		tree[pos]=arr[tl];
	}else{
		build(esq,tl,mid);
		build(dir,mid+1,tr);

		tree[pos]=combine(tree[esq],tree[dir]);
	}
}
void update(int pos, int tl, int tr, int x, int val){
	int esq=2*pos, dir=2*pos+1;
	int mid = (tl+tr)/2;
 
	if(tl==tr){
		arr[tl]=val;//assign update;
		tree[pos]=arr[tl];
	}else{
		if(x<=mid)update(esq,tl,mid,x,val);
		else update(dir,mid+1,tr,x,val);
 
		tree[pos]=combine(tree[esq],tree[dir]);
	}
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
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n,m;
	cin>>n>>m;
	init_(n);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	build(1,0,n-1);
	for(int i=0;i<m;i++){
		int op;
		cin>>op;
		if(op==1){
			int x,val;
			cin>>x>>val;
			update(1,0,n-1,x,val);
		}else{
			int l,r;
			cin>>l>>r;
			cout<<query(1,0,n-1,l,r-1).sum<<'\n';
		}
	}
	

	return 0;
}
