template<class T>
struct CoordinateCompression{
    vector<T>v;
    void push(const T &a){v.push_back(a);}
    int build(){
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        return (int)v.size();
    }
    int operator[](const T &a){ //first position greater or equal to a
        auto it=lower_bound(v.begin(),v.end(),a);
        return int( it-v.begin() );
    }
    bool count(const T &a){
        auto it=lower_bound(v.begin(),v.end(),a);
        return it != v.end() && *it == a;
    }
};