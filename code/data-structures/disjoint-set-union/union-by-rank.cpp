vector<int>p,r;
void init_(int n){
	p=vector<int>(n+1);//parent array
	iota(p.begin(),p.end(),0);

	r=vector<int>(n+1);
}
int get_set(int a){
	return p[a]=(p[a]==a?a:get_set(p[a]));//path compression
}

void union_set(int a, int b){
	a=get_set(a);
	b=get_set(b);

	if(a!=b){
		//Union by rank
		if(r[a]==r[b]){
			r[a]++;
		}

		if(r[a]>r[b])p[b]=a;
		else p[a]=b;
		
	}
}