const int ms = 1e6 + 10;
int phi[ms];
void sieve(){
    iota(phi, phi + ms, 0);
    for(int i = 1; i < ms; ++i){
        for(int j = 2 * i; j < ms; j += i){
            phi[j] -= phi[i];
        }
    }
}
