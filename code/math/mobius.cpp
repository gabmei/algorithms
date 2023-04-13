//https://www.quora.com/q/suryakiransposts/A-Dance-with-Mobius-Function
const int LIM = 1e6 + 10;
int mu[LIM];
bool pr[LIM];
vector<int> mask[LIM];
void build_mobius() {
  mu[1] = 1;
  for(int i = 1; i < LIM; ++i) {
    for(int j = 2 * i; j < LIM; j += i) {
      mu[j] -= mu[i];
    }
  }
}
void sieve() {
  fill(mu, mu + LIM, 1);
  memset(pr, 1, sizeof(pr));
  for(int i = 2; i < LIM; ++i) {
    if(pr[i]) {
      mu[i] = -1;
      for(int j = i + i; j < LIM; j += i) {
        mu[j] *= -1;
        pr[j] = false;
      }
      if(LIM / i / i == 0) {
        continue;
      }
      for(int sq = i * i, j = sq; j < LIM; j += sq) {
        mu[j] = 0;
      }
    }
  }
}
void build_mask() {
  for(int i = 2; i < LIM; ++i) {
    if(mu[i] != 0) {
      for(int j = i; j < LIM; j += i) {
        mask[j].emplace_back(i);
      }
    }
  }
}
