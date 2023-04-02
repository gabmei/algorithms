//we solve for x,y a*x+b*y==gcd(a,b) and return gcd(a,b)
ll gcd_ext(ll a, ll b, ll &x, ll &y){
  if(b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    ll nx, ny;
    ll g = gcd_ext(b, a % b, nx, ny);
    x = ny;
    y = nx - (a / b) * ny;
    return g;
  }
}
