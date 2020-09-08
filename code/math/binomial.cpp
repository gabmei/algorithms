typedef long long ll;
const ll mod = 1e9+7;
vector<ll>fat,fat_inv,inv; 
/*----------------------------------------------------------*/
//fat_inv[k] = modular inverse of k! mod m
//inv[k] = modular inverse of k mod m
//fat_inv[k] = fat_inv[k-1]*inv[k] mod m

//This implementation only works if m is prime

//Precalculates all inverses in O(n)
void fill_fat(int n){
	fat=fat_inv=inv=vector<ll>(n+1);
	for(int i=0;i<2;i++){
		fat[i]=fat_inv[i]=1;
	}
	inv[1]=1;

	for(ll i=2;i<=n;i++){
		fat[i]=fat[i-1]*i %mod;
		inv[i]=mod -(mod/i)*inv[mod%i]%mod;
		fat_inv[i]=fat_inv[i-1]*inv[i]%mod;
	}
}

ll comb(ll n, ll k){
	ll ret = fat[n]*fat_inv[k]%mod;
	return ret = ret*fat_inv[n-k]%mod;
}


/*----------------------------------------------------------*/
//a^(phi(m)-1)=a^-1 mod m
//a^(m-2)=a^-1 mod m if m prime
void fill_fat(int n){
	fat=vector<ll>(n+1,1);
	fat_inv=vector<ll>(n+1,-1);
	for(ll i=2;i<=n;i++){
		fat[i]=fat[i-1]*i %mod;
	}
}

ll binExp(ll b, ll e){
	ll ret=1;
	while(e){
		if(e&1){
			ret=ret*b %mod;
		}
		b=b*b %mod;
		e/=2;
	}
	return ret;
}

ll comb(ll n, ll k){
	if(fat_inv[k]==-1)fat_inv[k]=binExp(fat[k],mod-2);
	if(fat_inv[n-k]==-1)fat_inv[n-k]=binExp(fat[n-k],mod-2);
 
	ll ret = fat[n]*fat_inv[k]%mod;
	return ret = ret*fat_inv[n-k]%mod;
}



