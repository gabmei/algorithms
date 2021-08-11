template<class T>
struct PT{
    T x,y;
    PT(T x_=0,T y_=0):x(x_),y(y_){}
    PT operator +(const PT& o){return PT(x+o.x,y+o.y);}
    PT operator -(const PT& o){return PT(x-o.x,y-o.y);}
    T operator *(const PT& o){return x*o.x + y*o.y;}//dot product
    T operator ^(const PT& o){return x*o.y-y*o.x;}//cross product
    PT operator *(T c){return PT(x*c,y*c);}
    PT operator /(T c){return PT(x/c,y/c);}
    bool operator == (const PT& o){return x==o.x && y==o.y;}
    friend ostream& operator<< (ostream& os, PT& o) { return os << o.x <<' '<< o.y; }
    friend istream& operator>> (istream& is, PT& o) { return is >> o.x >> o.y; }
};
//square distance between points A and B
template<class T>
T distance(PT<T> A, PT<T> B){
	return (A-B)*(A-B);
}
//square distance between segment [A,B] and point C
template<class T>
T pointSegmentDistance(PT<T> A, PT<T> B, PT<T> C){
	PT<T> AB = B - A, AC = C - A, BC = C - B;
	if(AB * AC <= 0)return distance(A,C);
	if(BC * AB >= 0)return distance(B,C);
	return (AB ^ AC) * (AB ^ AC) / ( AB * AB );
}
//square distance between segments [A,B] and [C,D]
template<class T>
T segmentSegmentDistance(PT<T> A, PT<T> B, PT<T> C, PT<T> D){
	T mn1 = min(pointSegmentDistance(A,B,C),pointSegmentDistance(A,B,D));
	T mn2 = min(pointSegmentDistance(C,D,A),pointSegmentDistance(C,D,B));
	return min(mn1,mn2);
}

template<class T>
PT<double> lineIntersection(PT<T> a, PT<T> b, PT<T> c, PT<T> d){
	b = b - a; d = d - c; c = c - a;
	double x = PT<double>(c.x,c.y) ^ PT<double>(d.x,d.y);
	double y = PT<double>(b.x,b.y) ^ PT<double>(d.x,d.y);
	assert(fabs(y) > eps);
	double t = x / y;
	return PT<double>(a.x + t * b.x, a.y + t * b.y);
}
