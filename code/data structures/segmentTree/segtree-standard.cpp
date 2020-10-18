//count number of inversions

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
	ll sum;
	node(ll sum):sum(sum){};
}nil(0ll);

vector<node>tree;

void init_(int n){
	tree.assign(4*(n+2),nil);
}

node combine(const node& a,const node& b){
	return node(a.sum+b.sum);
}
void update(int pos, int tl, int tr, int x){
	int esq=2*pos, dir=2*pos+1;
	int mid = (tl+tr)/2;
 
	if(tl==tr){
		tree[pos].sum++;
	}else{
		if(x<=mid)update(esq,tl,mid,x);
		else update(dir,mid+1,tr,x);
 
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

	int n;
	cin>>n;
	init_(n);
	for(int i=0;i<n;i++){
		int a;cin>>a;

		cout<<query(1,1,n,a+1,n).sum<<' ';
		update(1,1,n,a);
	}
	

	return 0;
}