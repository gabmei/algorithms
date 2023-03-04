const int LIM = 1e6+10;
long long sum_div[LIM]; //sum_div[i] =sum of divisors of i
void sieve() {
  for(int i = 1; i < LIM; ++i) {
    for(int j = 2 * i ; j < LIM; j +=i) {
      sum_div[j] += i;
    }
  }
}

