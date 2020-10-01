#include<bits/stdc++.h>
using namespace std;
const int inf=1e5;

int cap[40][40];
vector<vector<int>>adj;

int bfs(int s, int t,vector<int> &parent){
	fill(parent.begin(),parent.end(),-1);

	parent[s]=-2;

	queue<pair<int,int>> q;
	q.push({s,inf});
	while(!q.empty()){
		int u = q.front().first;
		int flow=q.front().second;

		q.pop();

		for(int v:adj[u]){
			if(parent[v]==-1 && cap[u][v]>0){
				parent[v]=u;
				int new_flow=min(flow,cap[u][v]);

				if(v==t){
					return new_flow;
				}
				q.push({v,new_flow});
			}
		}
	}

	return 0;

}

int maxflow(int s, int t){
	int flow=0;
	vector<int>parent(t+1);
	int new_flow;

	while(new_flow = bfs(s,t,parent)){
		
		flow+=new_flow;
		int cur=t;
		while(cur!=s){
			int prev = parent[cur];
			cap[prev][cur]-=new_flow;
			cap[cur][prev]+=new_flow;
			cur=prev;
		}
	}
	return flow;
}

string get_ans(){
	int t=37;
	
	int mf = maxflow(0,t);
	
	bool flag=true;

	for(int i=1;i<=26;i++){
		if(cap[0][i]>0)flag=false;
	}

	string ans="";

	if(flag){
		for(int i=27;i<t;i++){
			int prev=-1;

			for(int a=1;a<=26;a++){
				if(cap[i][a]==1){
					prev=a;
				}
			}

			if(prev==-1){
				ans+='_';
			}else{
				char c ='A'+ (prev - 1);
				ans+=c;
			}
		}
	}else{
		ans+='!';
	}

	for(int i=0;i<=t;i++){
		adj[i].resize(0);
	}
	memset(cap,0,sizeof(cap));
	return ans;
}

int main(){
	int s=0,t=37;
	adj.resize(t+1);
	string str;
	while(getline(cin,str)){
		
		if(int(str.size())==1){
			string ans = get_ans();
			cout<<ans<<'\n';
		}else{
			int u = (str[0]-'A') +1;
			int cnt = (str[1]-'0');
			adj[s].push_back(u);
			cap[s][u]=cnt;

			for(int i=3;str[i]!=';';i++){
				int v = (str[i]-'0')+27;

				adj[v].push_back(t);
				cap[v][t]=1;


				adj[u].push_back(v);
				adj[v].push_back(u);
				cap[u][v]=1;
			}

		}
	}
	string ans=get_ans();
	cout<<ans<<'\n';

	return 0;
}