const int max_item_cnt=100+10;
const int max_knapsack_size=1e5+10;

ll W[max_item_cnt],V[max_item_cnt];
ll dp[max_item_cnt][max_knapsack_size]; // dp[i][j] - max sum of values from 1-th to i-th item and j space
bool sol[max_item_cnt]; //boolean array to retrieve solution
	
for(int i=1;i<=n;i++){
	for(int j=0;j<=w;j++)
		if(j>=W[i]){
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-W[i]]+V[i]);//either choose i-th item or not
		}else{
			dp[i][j]=dp[i-1][j];
		}
}
ll ans=dp[n][w];
ll wei=w;
for(int i=n;i>=1;i--){
	if(dp[i-1][wei]==dp[i][wei]){
		continue;
	}
	sol[i]=true;// i-th item was used
	wei-=W[i];
}