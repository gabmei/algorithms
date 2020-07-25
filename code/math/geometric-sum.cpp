//S(k) = I + A + A^2 + ... + A^k-1
/*----------------------------------------------------------*/
//Recursive geometric sum implementation
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
//Iterative geometric sum implementation
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
/*----------------------------------------------------------*/
