const int N = 2, mod=1e9+7;
 
template<class T>
T binExp(T a, long long e){
    T r(1);
    while(e){
        if(e&1)r=r*a;
        a=a*a;
        e>>=1;
    }
    return r;
}
 
struct MB{
    int x;
    MB(int _x=0):x(_x){}
    MB operator +(const MB& o){ return x+o.x >=mod ? x+o.x-mod : x+o.x; }
    MB operator -(const MB& o){ return x-o.x < 0 ? x-o.x+mod : x-o.x; }
    MB operator *(const MB& o){ return int(1ll*x*o.x%mod); }
    friend ostream& operator<< (ostream& os, MB& o) { return os << o.x; }
    friend istream& operator>> (istream& is, MB& o) { return is >> o.x; }
};
 
template<class T>
struct Matrix {
	vector<vector<T>>a;
	Matrix(bool identity=false):a(N,vector<T>(N)){
		for(int i=0;i<N;++i)a[i][i] = T(identity);
	}
	Matrix operator *(const Matrix& b){
		Matrix p;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				for(int k=0;k<N;k++)
					p.a[i][k]=p.a[i][k] + a[i][j]*b.a[j][k];
		return p;
	}
};
