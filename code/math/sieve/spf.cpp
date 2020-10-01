typedef long long ll;
const int lim = 1e6+10;
int spf[lim];//spf[i]=smallest prime factor of i
void sieve(int lim){
	iota(spf,spf+lim,0);//initially spf[i]=i
	for(int i=2;i<lim;i++){
		if(spf[i]==i){
			if((ll)i*i > lim)continue;
			for(int j=i*i;j<lim;j+=i){
				if(spf[j]==j)spf[j]=i;
			}
		}
	}
}
vector<int> get_primes(int x){//get all prime factors of a number
	vector<int>ret;
	while(x!=1){
		int p = spf[x];
		ret.push_back(p);
		while(x%p==0){
			x/=p;
		}
	}
	return ret;
}