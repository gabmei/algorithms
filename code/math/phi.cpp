const int LIM = 1e6 + 10;
int phi[LIM];
void sieve(){
  iota(phi, phi + LIM, 0);
  for(int i = 1; i < LIM; ++i){
    for(int j = 2 * i; j < LIM; j += i){
      phi[j] -= phi[i];
    }
  }
}

ll phi(ll n) {
	// initial answer
	ll ans = n;
	for(ll p = 2; p * p <= n; ++p) {
		if(n % p == 0) { //p is prime
			ans -= ans / p;
			while(n % p==0) n /= p;
		}
	}
	// we found no prime p<=sqrt(n) which means n is prime
	if(n > 1) {
		ans -= ans / n;
	}
	return ans;
}