#include<bits/stdc++.h>
using namespace std;
template<class T>
vector<int> getBorder(const T& s){
    int n = (int)s.size();
    vector<int>border(n);
    for(int i=1,j=0;i<n;++i){
        while(j>0 && s[i] != s[j]){
            j=border[j-1];
        }
        if(s[i] == s[j]){
            ++j;
        }
        border[i]=j;
    }
    return border;
}

template<class T, class F>
void matchPattern(const T& txt, const T& pat, const vector<int>& border, F get){
    int n = (int)txt.size();
    int m = (int)pat.size();
    for(int i=0,j=0;i<n;++i){
        while(j>0 && txt[i] != pat[j]){
            j=border[j-1];
        }
        if(txt[i] == pat[j]){
            ++j;
        }
        if(j==m){
            get(i-m+1);
            j=border[j-1];
        }

    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        string t,p;
        cin>>t>>p;
        vector<int>border=getBorder(p),ans;
        matchPattern(t,p,border,[&](int d){
            ans.push_back(d+1);
        });
        if(ans.empty()){
            cout<<"Not Found\n";
        }else{
            cout<<(int)ans.size()<<'\n';
            for(int d : ans){
                cout<<d<<' ';
            }
            cout<<'\n';
        }
    }
    return 0;
}
