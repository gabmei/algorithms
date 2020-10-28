#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int>p;
	vector<vector<int>>l;
    DSU(int n):p(n),l(n){//0-based
        for(int i=0;i<n;i++){
        	p[i]=i,l[i]={i};
        }
    }
    int getSet(int a){
		return p[a];
	}
    void unionSet(int a, int b){
		a=getSet(a);
		b=getSet(b);

		if(a!=b){
			if(l[a].size()>l[b].size()){
				swap(a,b);
			}
			while(!l[a].empty()){	
				int u=l[a].back();
				p[u]=b;

				l[b].push_back(u);
				l[a].pop_back();
			}
		}
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n,m,k;
	cin>>n>>m>>k;
	DSU dsu(n);

	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
	}

	vector<vector<int>>foo;
	for(int i=0;i<k;i++){
		string a;
		cin>>a;
		int u,v;
		cin>>u>>v;
		u--;v--;
		int tmp=a[0]=='c';
		foo.push_back({tmp,u,v});
	}
	
	reverse(foo.begin(),foo.end());

	vector<string>ans;

	for(auto& v:foo){
		//cout<<v[0]<<' '<<v[1]<<' '<<v[2]<<'\n';
		
		if(v[0]==1){//join
			dsu.unionSet(v[1],v[2]);
		}else{
			if(dsu.getSet(v[1])==dsu.getSet(v[2])){
				ans.push_back("YES");
			}else{
				ans.push_back("NO");
			}
		}
		
	}
	
	reverse(ans.begin(),ans.end());
	for(string& s:ans){
		cout<<s<<'\n';
	}
	
	return 0;
}
