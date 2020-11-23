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
			dsu.unionSet(u,v);
		}else if(op == "get"){
			if(dsu.getSet(u)==dsu.getSet(v)){
				cout<<"YES\n";
			}else{
				cout<<"NO\n";
			}
		}
	}
	
	
	
	return 0;
}
