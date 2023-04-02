//https://www.quora.com/q/suryakiransposts/A-Dance-with-Mobius-Function
const int LIM = 1e6 + 10;
int mu[LIM];
vector<int> mask[LIM];

void sieve() {
  mu[1] = 1;
  for(int i = 1; i < LIM; ++i) {
    for(int j = 2 * i; j < LIM; j += i) {
      mu[j] -= mu[i];
    }
  }
  for(int i = 2; i < LIM; ++i) {
    if(mu[i] != 0) {
      for(int j = i; j < LIM; j += i) {
        mask[j].emplace_back(i);
      }
    }
  }
}
