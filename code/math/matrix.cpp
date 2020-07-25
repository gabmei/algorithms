typedef long long ll;
const ll mod = 1e9+7;
const int N = 2;

template<class T>
struct Matrix {
	vector<vector<T>>a;
	Matrix(){
		a=vector<vector<T>>(N,vector<T>(N));
	}
	void identity(){
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)a[i][j]=(i==j);
	}
	Matrix operator *(Matrix const &b){
		Matrix p;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				for(int k=0;k<N;k++){
					p.a[i][j]=(p.a[i][j] + a[i][k]*b.a[k][j])%mod;
				}
			}
		}
		return p;
	}
	Matrix operator +(Matrix const &b){
		Matrix s;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				s.a[i][j]=(a[i][j] + b.a[i][j])%mod;
			}
		}
		return s;
	}
	void binExp(ll exp){
		Matrix<T> ans;ans.identity();
		
		while(exp>0){
			if(exp & 1)ans=ans*(*this);
			exp/=2;
			(*this)=(*this)*(*this);
		}

		(*this) = ans;
	}
};
/*----------------------------------------------------------*/
//Recursive geometric sum
template<class T>
Matrix<T> GP_sum(Matrix<T> &ratio, ll n){
	Matrix<T> ret;
	if(n==0)return ret;
	Matrix<T> I,A;
	I.identity();
	A=ratio;
	A.binExp(n/2);
	if(n%2==1)ret=A,A=A*ratio;

	return ret=ret + (I+A)*GP_sum(ratio,n/2);
}
/*----------------------------------------------------------*/
//Iterative geometric sum
template<class T>
Matrix<T> GP_sum(Matrix<T> &ratio, ll n){

	Matrix<T> ans,I,ans_pot,magic;
	I.identity();
	magic=I;
	ans_pot=I;
	while(n>0){
		if(n&1){
			ans = ans_pot*magic + ans;
			ans_pot=ans_pot*ratio;
		}
		magic = ratio*magic + magic;
		ratio=ratio*ratio;
		n/=2;
	}

	return ans;
}
/*-----------------------------------------------*/
