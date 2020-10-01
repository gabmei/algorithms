/*----------------------------------------------------------------------------------------------*/
//standard dsu
vector<int>p,r,sz;
void init_(int n){
	p=vector<int>(n+1);//parent array
	iota(p.begin(),p.end(),0);

	r=vector<int>(n+1);//rank array
	sz=vector<int>(n+1,1);//size array
}
int get_set(int a){
	return p[a]=(p[a]==a?a:get_set(p[a]));//path compression
}

void union_set(int a, int b){
	a=get_set(a);
	b=get_set(b);

	if(a!=b){
		/* //Union by rank
		if(r[a]==r[b]){
			r[a]++;
		}
		if(r[a]>r[b]){
			p[b]=a;
		}else{
			p[a]=b;
		}
		*/
		/* //Union by size
		if(sz[a]>sz[b]){
			swap(a,b);
		}
		p[a]=b;
		sz[b]+=sz[a];
		*/

	}
}

/*----------------------------------------------------------------------------------------------*/
//storing all values of a component
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
