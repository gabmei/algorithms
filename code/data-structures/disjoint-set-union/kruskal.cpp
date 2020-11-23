#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int>p,sz;
    DSU(int n):p(n),sz(n){//0-based
        iota(p.begin(),p.end(),0);
        fill(sz.begin(),sz.end(),1);
    }
    int getSet(int a){
        return p[a]=(p[a]==a?a:getSet(p[a]));//path compression
    }
    void unionSet(int a, int b){
        a=getSet(a);
        b=getSet(b);
 
        if(a!=b){
            //Union by size
            if(sz[a]>sz[b]){
                swap(a,b);
            }
            p[a]=b;
            sz[b]+=sz[a];
        }
    }
    int countSets(){
    	int n = (int)p.size(),cnt=0;
    	for(int i=0;i<n;i++){
    		cnt+=i==getSet(i);
    	}
    	return cnt;
    }
};

struct Edge{
	int u,v,w;
	Edge(int u,int v, int w):u(u),v(v),w(w){}
	bool operator<(const Edge& a){ // operator for sort function
		return w < a.w;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n,m;
	cin>>n>>m;
	DSU dsu(n);
	vector<Edge>edges;
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u--;v--;
		edges.emplace_back(u,v,w);
	}
	sort(edges.begin(),edges.end());
	long long total_cost=0;
	for(Edge e:edges){
		if(dsu.getSet(e.u)!=dsu.getSet(e.v)){//get edges with lowest values
			total_cost+=e.w;
			dsu.unionSet(e.u,e.v);
		}
	}
	cout<<total_cost<<'\n';
	
	return 0;
}
