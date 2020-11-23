/*
	https://www.spoj.com/problems/MKTHNUM/
	K-th order statistic problem
	Persistent Data Structure with pointers implementation
	O((n+m)log(n))
	Time:0.55, MEM:51M
*/
#include<bits/stdc++.h>
using namespace std;

const int ms = 1e5;	
struct Node{
	int v=0;
	Node *l = this, *r = this;
};
Node buffer[20 * ms]; // memory allocation for the nodes;
Node *root[ms + 1]; // root[i] - pointer to the root of version i
int cnt = 0;
Node *update(Node *on, int tl, int tr, int x, int val){
	Node *node = &buffer[cnt++];
	*node = *on;
	if(tl==tr){
		node->v=val;
		return node;
	}else{
		int mid = (tl+tr)/2;
		if(x<=mid)node->l=update(on->l,tl,mid,x,val);
		else node->r=update(on->r,mid+1,tr,x,val);
		
		node->v = node->l->v + node->r->v;
		return node;
	}
}

int query(Node *onOld, Node *onNew,int tl, int tr, int k){
	if(tl==tr){
		return tl;
	}else{
		int mid = (tl+tr)/2;
		int cnt = onNew->l->v - onOld->l->v;
		if(cnt>=k){
			return query(onOld->l,onNew->l,tl,mid,k);
		}else{
			return query(onOld->r,onNew->r,mid+1,tr,k-cnt);
		}
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin>>n>>m;
	vector<pair<int,int>>a(n);
	vector<int>b(n);
	for(int i=0;i<n;i++){
		cin>>a[i].first;
		a[i].second=i;
	}
	sort(a.begin(),a.end());
	for(int i=0;i<n;i++){
		int j = a[i].second;
		b[j]=i;
	}

	root[0] = &buffer[cnt++];
	for(int i=1;i<=n;i++){
		root[i]=update(root[i-1],0,n-1,b[i-1],1);
	}
	for(int i=0;i<m;i++){
		int l,r,k;
		cin>>l>>r>>k;
		int id = query(root[l-1],root[r],0,n-1,k);
		cout<<a[id].first<<'\n';
	}
	return 0;
}