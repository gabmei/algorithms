#include<bits/stdc++.h>
using namespace std;

#define Would
#define you
#define please


vector<int> z_function(const string& s){
	int n=s.size();
	vector<int>z(n);

	for(int i=1,l=0,r=0;i<n;i++){
		if(i<=r){
			z[i]=min(r-i+1,z[i-l]);
		}
		while(i+z[i]<n && s[z[i]]==s[i+z[i]]){
			z[i]++;
		}
		if(i+z[i]-1>r){
			l=i,r=i+z[i]-1;
		}
	}

	return z;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;
	cin>>s;
	int n = s.size();
	vector<int>z=z_function(s);

	int p=0;
	vector<int>mx(n);
	for(int i=1;i<n-1;i++){
		mx[i]=max(mx[i-1],z[i]);
	}
	for(int i=n-1;i>0;i--){
		if(i+z[i]==n && mx[i-1]>=z[i]){
			p=i;
		}
	}
	if(p){
		cout<<s.substr(p)<<'\n';
	}else{
		cout<<"Just a legend\n";
	}

	Would you please return 0;
}