const int LIM = 1e6+10;
int num_div[LIM]; //num_div[i] = number of divisors of i
void sieve() {
  for(int i = 1; i < LIM; ++i) {
    for(int j = i; j < LIM; j += i) {
      num_div[j]++;
    }
  }
}