#include<bits/stdc++.h>
using namespace std;

vector<int>p,sz;
void init_(int n){
	p=vector<int>(n+1);
	iota(p.begin(),p.end(),0);

	sz=vector<int>(n+1,1);
}
int get_set(int a){
	return p[a]=(p[a]==a?a:get_set(p[a]));//path compression
}

void union_set(int a, int b){
	a=get_set(a);
	b=get_set(b);

	if(a!=b){
		//Union by size
		if(sz[a]>sz[b]){
			swap(a,b);
		}
		p[a]=b;
		sz[b]+=sz[a];

	}
}
struct Edge{
	int u,v,w;
	Edge(int u,int v, int w):u(u),v(v),w(w){}
	bool operator<(const Edge& a){ // operator for sort function
		return w < a.w;
	}
};

vector<Edge>edges;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n,m;
	cin>>n>>m;
	init_(n);

	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		edges.emplace_back(u,v,w);
	}
	sort(edges.begin(),edges.end());
	long long total_cost=0;
	for(Edge e:edges){
		if(get_set(e.u)!=get_set(e.v)){//get edges with lowest values
			total_cost+=e.w;
			union_set(e.u,e.v);
		}
	}
	cout<<total_cost<<'\n';
	
	return 0;
}