//storing all values of a component
vector<int>p;
vector<vector<int>>l;
void init_(int n){
	p=vector<int>(n+1);//parent array
	l=vector<vector<int>>(n+1);//l[get_set[i]] stores all values of this component

	for(int i=1;i<=n;i++){
		p[i]=i;
		l[i]={i};
	}
}
int get_set(int a){
	return p[a];
}

void union_set(int a, int b){
	a=get_set(a);
	b=get_set(b);

	if(a!=b){
		//union small to large
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
