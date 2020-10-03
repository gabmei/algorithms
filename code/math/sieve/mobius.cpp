//https://www.quora.com/q/suryakiransposts/A-Dance-with-Mobius-Function
typedef long long ll;
const int lim=1e6+100;
bool is_prime[lim];
int mu[lim];
void sieve(int lim){
	for(int i=1;i<lim;i++){
		is_prime[i]=true;
		mu[i]=1;
	}
	is_prime[1]=is_prime[0]=false;
	for(int i=2;i<lim;i++){
		if(is_prime[i]){
			mu[i]=-1;
			for(int j=2*i;j<lim;j+=i){
				mu[j]*=-1;
				is_prime[j]=false;
			}
			ll sq=(ll)i*i;
			for(ll j=sq;j<lim;j+=sq){
				mu[j]=0;
			}
		}
	}
}
