template<class T>
struct RMQ{
	int N;
	int K=25;
	vector<vector<T>>st;
	RMQ(){};
	RMQ(const vector<T>& V){
		N=V.size();
		st=vector<vector<T>>(K+1,vector<T>(N));
		for(int i=0;i<N;i++){
			st[0][i]=V[i];
		}
		for(int j=1;j<=K;j++){
			for(int i=0;i+(1<<j)<=N;i++){
				st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
			}
		}
	}
	T query(int l, int r){
		int j = 31-__builtin_clz(r-l+1);
		return min(st[j][l],st[j][r-(1<<j)+1]);
	}
};