ll phi(ll n){
	// initial answer
	ll ans = n;

	for(ll p=2;p*p<=n;p++){
		if(n%p==0){ //p is prime
			ans-=ans/p;
			while(n%p==0)n/=p;
		}
	}
	//we found no prime p<=sqrt(n) which means n is prime
	if(n>1){
		ans-=ans/n;
	}
	return ans;
}

ll PHI(){ //phi[i]== phi(i)
	for(ll i=1;i<=lim;i++) phi[i]=i;
	for(ll i=2;i<=lim;i++){
		if(phi[i]==i){//i is prime
			for(ll j=i;j<=lim;j+=i){//i is prime factor of j's
				phi[j]=(phi[j]/i)*(i-1);
			}
		}
	}
}
