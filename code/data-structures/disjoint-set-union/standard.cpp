struct DSU{
    vector<int>p,sz;
    DSU(int n):p(n),sz(n){//0-based
        iota(p.begin(),p.end(),0);
        fill(sz.begin(),sz.end(),1);
    }
    int root(int a){
        return p[a]=(p[a]==a?a:root(p[a]));//path compression
    }
    void unite(int a, int b){
        a=root(a);
        b=root(b);
 
        if(a!=b){
            //Union by size
            if(sz[a]<sz[b]){
                swap(a,b);
            }
            p[b]=a;
            sz[a]+=sz[b];
        }
    }
    int size(int x){
        return sz[root(x)];
    }
    int count(){
    	int n = (int)p.size(),cnt=0;
    	for(int i=0;i<n;i++){
    		cnt+=i==root(i) ? 1 : 0;
    	}
    	return cnt;
    }
};
