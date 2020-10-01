typedef long long ll;
const int lim=1e6+10;
ll sum_div[lim];//sum_div[i] =sum of divisors of i
void sieve(int lim){
	for(int i=1;i<lim;i++){
		for(int j=2*i;j<lim;j+=i){
			sum_div[j]+=i;
		}
	}
}

