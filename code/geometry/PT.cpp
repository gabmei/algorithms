struct PT{
    double x,y;
    PT(double x_=0,double y_=0):x(x_),y(y_){}
    PT operator +(const PT& o){return PT(x+o.x,y+o.y);}
    PT operator -(const PT& o){return PT(x-o.x,y-o.y);}
    double operator *(const PT& o){return x*o.x + y*o.y;}//dot product
    double operator ^(const PT& o){return x*o.y-y*o.x;}//cross product
    PT operator *(double c){return PT(x*c,y*c);}
    PT operator /(double c){return PT(x/c,y/c);}
    friend ostream& operator<< (ostream& os, PT& o) { return os << o.x <<' '<< o.y; }
    friend istream& operator>> (istream& is, PT& o) { return is >> o.x >> o.y; }
};
