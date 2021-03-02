#include<bits/stdc++.h>
using namespace std;
template<class T>
struct KMP{
    int id(char x){return x - 'a';}
    int n,sigma;
    vector<vector<int>>aut;
    KMP(const T& pat, int _sigma=26){
        n=(int)pat.size();
        sigma=_sigma;
        aut.assign(n+1,vector<int>(sigma));
        aut[0][id(pat[0])]=1;
        for(int i=1,j=0;i<=n;++i){
            copy(aut[j].begin(),aut[j].end(),aut[i].begin());
            if(i<n){
                int c = id(pat[i]);
                aut[i][c] = i+1;
                j=aut[j][c];
            }
        }
    }
    template<class F>
    void matchPattern(const T& txt, F get){
        int m = (int)txt.size();
        for(int i=0,j=0;i<m;++i){
            j=aut[j][id(txt[i])];
            if(j == n){
                get(i-n+1);
            }
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;cin>>T;
    while(T--){
        string t,p;
        cin>>t>>p;
        KMP<string>aut(p);
        vector<int>ans;
        aut.matchPattern(t,[&](int d){
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
