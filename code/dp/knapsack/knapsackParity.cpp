//----------------------------------------------------------------//
//standard knapsack

ll W[max_item_cnt],V[max_item_cnt];
ll dp[2][max_knapsack_size]; 
//dp[i][j] - max sum of values with j space from 1-th to i-th (only i's parity matters)
for(int i=1;i<=n;i++){
		int t=i%2;
		for(int j=0;j<=w;j++){
			if(j>=W[i]){
				dp[t][j]=max(dp[!t][j],dp[!t][j-W[i]]+V[i]);
			}else{
				dp[t][j]=dp[!t][j];
			}
		}
	}
	ll ans=dp[n%2][w];
	cout<<ans;



//----------------------------------------------------------------//
//this is in the case weights are too large

ll W[max_item_cnt],V[max_item_cnt];
ll dp[2][max_value_possible];
//dp[i][j]-min weight to get at least j space from  1-th to i-th element(only i's parity matters)

for(int i=1;i<max_value_possible;i++){
		dp[0][i]=dp[1][i]=inf;
}
for(int i=1;i<=n;i++){
	int t = i%2;
	for(int j=0;j<=max_val;j++){
		if(j>=V[i]){
			dp[t][j]=min(dp[!t][j],dp[!t][j-V[i]]+W[i]);
		}else{
			dp[t][j]=dp[!t][j];
		}
		
	}
}
int ans=0;
for(int v=max_val;v>=0 && !ans;v--){
	if(dp[n%2][v]<=w){
		ans=v;
	}
}

cout<<ans;
