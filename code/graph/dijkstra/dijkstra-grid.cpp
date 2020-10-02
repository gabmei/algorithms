#include<bits/stdc++.h>
using namespace std;
const int inf = 1e8;

int dx[4]={1,0,-1,0};// all possibles movements
int dy[4]={0,1,0,-1};
int n,m;
vector<string>grid;
int dijkstra(int xs, int ys,int xt, int yt){
	//minimum distance from ={xs,ys}, to={xt,yt}  
	vector<vector<int>>dist(n,vector<int>(m,inf));
	dist[xs][ys]=0;

	using piii=pair<int,pair<int,int>>;
	priority_queue<piii,vector<piii>,greater<piii>>pq;
	pq.push({dist[xs][ys],{xs,ys}});
	//if weights are all 1-0, we could use a deque instead
	//if weights are all 1, a queue is also possible
	while(!pq.empty()){
		piii node=pq.top();
		pq.pop();

		int x,y,distxy;
		x=node.second.first,y=node.second.second,distxy=node.first;

		if(distxy!=dist[x][y]){
			//dist to {x,y} is not updated
			continue;
		}
		//dist[x][y] is already minimum

		for(int dir=0;dir<4;dir++){
			int nx=x+dx[dir];
			int ny=y+dy[dir];

			if(nx<0||ny<0||nx>=n||ny>=m || grid[nx][ny]=='#'){
				//invalid position
				break;
			}
			//all weights are one in this problem
			if(dist[x][y]+1<dist[nx][ny]){
				dist[nx][ny]=1+dist[x][y];

				pq.push({dist[nx][ny],{nx,ny}});
			}
		}
	}

	//returns the distance to {xt,yt} or -1 if impossible
	return (dist[xt][yt]==inf?-1:dist[xt][yt]);

}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin>>n>>m;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		grid.push_back(s);
	}
	int xs,ys,xt,yt;
	cin>>xs>>ys>>xt>>yt;
	xs--;ys--;xt--;yt--;
	cout<<dijkstra(xs,ys,xt,yt)<<'\n';
	

	return 0;
}