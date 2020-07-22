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
