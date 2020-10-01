const int lim=1e6+10;
int num_div[lim];//num_div[i] = number of divisors of i
void sieve(int lim){
	for(int i=1;i<lim;i++){
		for(int j=i;j<lim;j+=i){
			num_div[j]++;
		}
	}
}