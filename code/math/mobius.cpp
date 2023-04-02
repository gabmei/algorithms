//https://www.quora.com/q/suryakiransposts/A-Dance-with-Mobius-Function
typedef long long ll;
const int LIM=1e6+100;
bool is_prime[LIM];
int mu[LIM];
void sieve() {
  for(int i = 1; i < LIM; ++i) {
    is_prime[i] = true;
    mu[i] = 1;
  }
  is_prime[1] = is_prime[0] = false;
  for(int i = 2; i < LIM; ++i) {
    if(is_prime[i]) {
      mu[i] = -1;
      for(int j = 2 * i; j < LIM; j += i) {
        mu[j] *= -1;
        is_prime[j] =false;
      }
      //LIM <= i * i
      if(LIM / i / i == 0)continue;
      int sq = i * i;
      for(int j = sq; j < LIM; j += sq) {
        mu[j] = 0;
      }
    }
  }
}
