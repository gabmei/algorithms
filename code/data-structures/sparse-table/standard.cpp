template<class T>
struct sparseT{
	int N;
	int K=25;
	vector<vector<T>>st;
	T f(T a,T b){
		//returns f(a,b);
		//in case of range sum f(a,b)=a+b
	}
	T f(T a){
		//returns f(a);
	}
	T init_(){
		//returns initial value for query;
	}
	sparseT(){};
	sparseT(const vector<T>& V){
		N=V.size();
		st=vector<vector<T>>(K+1,vector<T>(N));
		for(int i=0;i<N;i++){
			st[0][i]=f(V[i]);
		}
		for(int j=1;j<=K;j++){
			for(int i=0;i+(1<<j)<=N;i++){
				st[j][i]=f(st[j-1][i],st[j-1][i+(1<<(j-1))]);
			}
		}
	}
	T query(int l, int r){
		T ret=init_();

		for(int j=K;j>=0;j--){
			if((1<<j)<=r-l+1){
				ret=f(ret,st[j][l]);
				l+=(1<<j);
			}
		}
		return ret;
	}
};
/*---------------------------------------------------*/
//For cyclic arrays
vector<vector<int>>st;

int l = 31;
int go(int u, int len){// walk len steps starting from u
	for(int j=0;j<l;j++){
		if((1<<j)&len){
			u=st[j][u];
		}
	}
	return u;
}

st=vector<vector<int>>(l+1,vector<int>(n));
for(int i=0;i<n;i++){
	st[0][i]=v[i];
}

for(int j=1;j<l;j++){
	for(int i=0;i<n;i++){
		st[j][i]=st[j-1][st[j-1][i]];
	}
}
