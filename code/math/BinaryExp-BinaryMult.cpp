/*-------------------------------------------------*/
const ll mod = 1e9+7;
ll binExp(ll base, ll exp) {
    ll ans=1;
    while (exp>0) {
        if (exp & 1)ans = ans * base % mod;
        base = base * base % mod;
        exp/=2;
    }
    return ans;
}
/*-------------------------------------------------*/
//returns base^exp %mod
ll BinExp(ll base, ll exp, ll mod){
	ll ans =1;
	while(exp){
		if(exp & 1){
			ans=BinMult(ans,base,mod);
		}
		base=BinMult(base,base,mod);
		exp/=2;
	}
	return ans;
}

//returns a*b %mod
ll BinMult(ll a, ll b, ll mod){
	ll ans=0;
	a%=mod;
	while(b){
		if(b & 1){
			ans=(ans+a)%mod;
		}
		a=(a*2)%mod;
		b/=2;
	}
	return ans;
}
