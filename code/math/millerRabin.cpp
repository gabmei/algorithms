ll BinMult(ll a, ll b, ll mod){//Binary Multiplication in case of overflow
	ll ans=0;
	a%=mod;
	while(b){
		if(b & 1){
			ans=(ans+a)%mod;
		}
		a=(a*2)%mod;
		b>>=1;
	}
	return ans;
}
 
ll BinExp(ll base, ll exp, ll mod){
	ll ans =1;
	while(exp){
		if(exp & 1){
			ans=BinMult(ans,base,mod);
		}
		base=BinMult(base,base,mod);
		exp>>=1;
	}
	return ans;
}
 
bool check_composite(ll num, ll base,ll d, ll s){
	ll x = BinExp(base,d,num);	
 
	if(x==1 ||x==num-1){
		return false;
	}
 
	for(int i=0;i<s;i++){
		x=BinMult(x,x,num);
		if(x==num-1){
			return false;
		}
	}
	return true;
}
 
bool MillerRabin(ll n){
	if(n<2){
		return false;
	}
	//n-1 == 2^s * d, n>2 && n%2==1
	ll s = 0;
	ll d=n-1;
 
	while((d & 1)==0){//
		d>>=1;
		s++;
	}
	//for n 32 bits we check 2,3,5,7
	//for n 64 bits we check the first 12 primes

	for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a){
        	return true;
        }
        if (check_composite(n, a, d, s)){
        	return false;
        }
    }
    return true;
}
