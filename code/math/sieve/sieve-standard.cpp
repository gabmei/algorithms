const int lim = 1e6+10;
bool is_prime[lim];
vector<int> sieve(int lim){
	memset(is_prime,1,sizeof(is_prime));
	is_prime[0]=is_prime[1]=false;
	vector<int> primes;
	for(int i=2;i<lim;i++){
		if(is_prime[i]){
			primes.push_back(i);
			if((ll)i*i > lim)continue;
			for(int j=i*i;j<lim;j+=i){
				is_prime[j]=false;
			}
		}
	}
	return primes;
}

ll num_div(int n,vector<int> &primes){
	if(n==1)return 1;
	if(binary_search(primes.begin(),primes.end(),n))return 2;

	ll ret=1;
	for(int p:primes){
		if(n==1)break;
		if(n%p==0){
			int exp=0;
			while(n%p==0){
				n/=p;
				exp++;
			}
			ret*=(exp+1);
		}
	}

	return ret;
}