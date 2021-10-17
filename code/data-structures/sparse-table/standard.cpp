template<class T>
struct SparseTable{
	int N, K;
	vector<vector<T>>st;
	T f(const T& a, const T& b){return max(a,b);}
	SparseTable(int _N):N(_N),K(ceil(log2(N))){}
	void build(const vector<T>& V){
		st.assign(K+1,vector<T>(N));
		for(int i=0;i<N;i++) st[0][i] = V[i];
		
		for(int j=1;j<=K;j++)
			for(int i=0;i+(1<<j)<=N;i++)
				st[j][i] = f(st[j-1][i], st[j-1][i+(1<<(j-1))]);
	}
	T query(int l, int r){
		int j = 31-__builtin_clz(r-l+1);
		return f(st[j][l], st[j][r-(1<<j)+1]);
	}
};
