int lcs[3030][3030]; 
//lcs[i][j] lcs from s[0...i-1] to t[0...j-1]
//in here strings are one based
string s,t;

memset(lcs,0,sizeof(lcs));
cin>>s>>t;
for(int i=1;i<=s.size();i++){
	for(int j=1;j<=t.size();j++){
		if(s[i-1]==t[j-1])
			lcs[i][j]=1+lcs[i-1][j-1];
		else
			lcs[i][j]=max(lcs[i-1][j],lcs[i][j-1]);

	}
}

//retrieving the lcs
int l,r;
l=s.size(),r=t.size();
string ret="";
while(lcs[l][r]>0){
	while(lcs[l-1][r]==lcs[l][r])l--;

	while(lcs[l][r-1]==lcs[l][r])r--;

	ret+=t[r-1];
	l--;
	r--;
}
reverse(ret.begin(),ret.end());
cout<<ret<<"\n";
