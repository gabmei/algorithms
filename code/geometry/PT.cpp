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
