//get primes up to sqrt(n)
bool is_prime[lim];
vector<int> sieve(int n){
	memset(is_prime,1,sizeof(is_prime));
	is_prime[0]=is_prime[1]=false;
	vector<int> primes;
	for(int i=2;i*i<n;i++){
		if(is_prime[i]){
			primes.push_back(i);
			if((ll)i*i > n)continue;
			for(int j=i*i;j<n;j+=i){
				is_prime[j]=false;
			}
		}
	}
	return primes;
}
 
ll num_div(int n,vector<int> &primes){
	ll ret=1;
	int m=n;
	for(int p:primes){
		if((ll)p*p>m)break;
		if(n%p==0){
			int exp=0;
			while(n%p==0){
				n/=p;
				exp++;
			}
			ret*=(exp+1);
		}
	}
	if(n>1)ret*=2;// n is prime
 
	return ret;
}
