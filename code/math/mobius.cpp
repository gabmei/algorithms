//https://www.quora.com/q/suryakiransposts/A-Dance-with-Mobius-Function
const int LIM = 1e6 + 10;
int mu[LIM];
void sieve() {
  mu[1] = 1;
  for(int i = 1; i < LIM; ++i) {
    for(int j = 2 * i; j < LIM; j += i) {
      mu[j] -= mu[i];
    }
  }
}
