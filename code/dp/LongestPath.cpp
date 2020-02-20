vector<int> G[100010];
vector<int> d(100010);

//Memoization for longest path in DAG
int depth(int u){
	if(G[u].size()==0){
		return d[u]=0;
	}else if(d[u]!=-1){
		return d[u];
	}else{
		int ret=0;
		for(int v: G[u]){
			ret = max(depth(v),ret);
		}
		return d[u]= 1 + ret;
	}
}


int ans=0;//size of the longest path
for(int i=1;i<=n;i++){
  ans=max(ans,depth(i));
}
