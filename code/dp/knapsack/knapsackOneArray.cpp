//------------------------------------//
//standard knapsack

const int max_item_cnt=100+10;
const int max_knapsack_size=1e5+10;
ll W[max_item_cnt],V[max_item_cnt];
ll dp[max_knapsack_size]; // dp[i] - max sum of values with i space
 
	
for(int i=1;i<=n;i++){
	for(int j=w;j>=W[i];j--){//go backwards to not repeat items
		dp[j]=max(dp[j],dp[j-W[i]]+V[i]);
	}
}

for(int i=1;i<=n;i++){
	for(int j=0;j+W[i]<=w;j++){//repetitions allowed
		dp[j+W[i]]=max(dp[j+W[i]],dp[j]+V[i]);
	}
}
ll best_solution=0;
for(int i=1;i<=w;i++){
	best_solution=max(best_solution,dp[i]);
}


//------------------------------------//
//in case weights too large

const int max_item_cnt=100+10;
const int max_value_sum=1e5+10;
ll W[max_item_cnt],V[max_item_cnt];
ll dp[max_value_sum]; 
// dp[i] - min sum of weights which values add up to i

for(int i=1;i<=max_val;i++)dp[i]=inf;	
for(int i=1;i<=n;i++){
	for(int j=max_val;j>=V[i];j--){//go backwards to not repeat items
		dp[j]=min(dp[j-V[i]]+W[i],dp[j]);
	}
}
ll best_solution=0;
//ans - max v such as dp[v]<=w
for(int v=max_val;v>=0 && !best_solution;v--){
	if(dp[v]<=w){
		best_solution=v;
	}
}
