#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf=1e12;
vector<vector<pair<int,ll>>> adj;

void dijkstra(int s,vector<ll>& d,vector<int>& p){
	int n=adj.size();
	d.assign(n,inf);
	p.assign(n,-1);

	d[s]=0;
	using pii=pair<ll,int>;
	priority_queue<pii,vector<pii>,greater<pii>>pq;
	pq.push({0ll,s});

	while(!pq.empty()){
		int u=pq.top().second;
		ll d_u=pq.top().first;
		pq.pop();

		if(d_u!=d[u]){
			//d_u is not updated
			continue;
		}
		//d[u] is already minimum

		for(auto edge:adj[u]){
			int v=edge.first;
			ll w=edge.second;

			if(d[u]+w<d[v]){
				d[v]=d[u]+w;
				p[v]=u;
				pq.push({d[v],v});
			}
		}
	}
}

vector<int> restore_path(int s, int t,const vector<int>& p){
	vector<int>ret;
	for(int v=t;v!=s;v=p[v]){
		ret.push_back(v);
	}
	ret.push_back(s);
	reverse(ret.begin(),ret.end());

	return ret;
}

int main(){

	return 0;
}