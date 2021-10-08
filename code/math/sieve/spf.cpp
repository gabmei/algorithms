const int ms = 1e5+10;
int spf[ms];//spf[i]=smallest prime factor of i
void sieve(){
	iota(spf,spf+ms,0);//initially spf[i]=i
	for(int i=2;i<ms;i++){
		if(spf[i]==i){
			if(1ll*i*i > ms)continue;
			for(int j=i*i;j<ms;j+=i){
				if(spf[j]==j)spf[j]=i;
			}
		}
	}
}
template<class T>
void getPrimes(int x, T get){
    while(x != 1){
        int p = spf[x];
        while(x%p==0){
            x/=p;
        }
        get(p);
    }
}

vector<int> getDivisors(int x){
	vector<int>divisors({1});
	while(x!=1){
		int p=spf[x];
		int e=0;
		while(x%p==0){x/=p;e++;}
		int n = (int)divisors.size();
		for(int i=0;i<n;i++){
			int u = divisors[i];
			for(int j=1,v=p;j<=e;j++,v*=p){
				divisors.push_back(u*v);
			}
		}
	}
	return divisors;
}
