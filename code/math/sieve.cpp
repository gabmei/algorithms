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