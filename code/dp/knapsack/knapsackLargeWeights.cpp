const int max_item_cnt=100+10;
const int max_knapsack_size=1e5+10;

ll W[max_item_cnt],V[max_item_cnt];
ll dp[max_item_cnt][max_value_possible];//dp[i][j]-min weight to get at least j space from 1-th to i-th element
bool sol[max_item_cnt];

for(int i=1;i<max_value_possible;i++){
		dp[0][i]=inf;
}
for(int i=1;i<=n;i++){
	for(int j=0;j<=max_val;j++){
		if(j>=V[i]){
			dp[i][j]=min(dp[i-1][j],dp[i-1][j-V[i]]+W[i]);
		}else{
			dp[i][j]=dp[i-1][j];
		}
		
	}
}
int ans=0;
//ans - biggest such as dp[n][v]<=w
for(int v=max_val;v>=0 && !ans;v--){
	if(dp[n][v]<=w){
		ans=v;
	}
}
int val=ans;
for(int i=n;i>=1;i--){
	if(dp[i-1][val]==dp[i][val]){
		continue;
	}
	sol[i]=true;
	val-=V[i];
}
	