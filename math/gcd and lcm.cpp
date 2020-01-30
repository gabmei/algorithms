ll gcd(ll a, ll b){return b==0? a:gcd(b,a%b);}


//gcd(a,b)*lcm(a,b)==a*b
ll lcm(ll a, ll b){
	return (a/gcd(a,b))*b;
}

//we solve for x,y a*x+b*y==gcd(a,b) and return gcd(a,b)
ll gcd_ext(ll a, ll b, ll &x, ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}else{
		ll nx,ny;
		ll gc = gcd_ext(b,a%b,nx,ny);
		x=ny;
		y=nx-(a/b)*ny;
		return gc;
	}
}