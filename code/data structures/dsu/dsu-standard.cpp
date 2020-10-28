#include<bits/stdc++.h>
using namespace std;

struct DSU{
    int n;
    vector<int>p,sz;
    DSU(int n):n(n),p(n),sz(n){//0-based
        iota(p.begin(),p.end(),0);
        fill(sz.begin(),sz.end(),1);
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
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,m;
	cin>>n>>m;
	DSU dsu(n);

	for(int i=0;i<m;i++){
		string op;
		int u,v;
		cin>>op>>u>>v;
		u--;v--;
		if(op=="union"){
			dsu.union_set(u,v);
		}else if(op == "get"){
			if(dsu.get_set(u)==dsu.get_set(v)){
				cout<<"YES\n";
			}else{
				cout<<"NO\n";
			}
		}
	}
	
	
	
	return 0;
}
