// thanks to: https://github.com/celiopassos/competitive-programming/blob/master/Graphs/tarjan.cpp
// scc ids are sorted in reverse order
// edge uv imples scc[u] >= scc[v]
// it is garanteed that 0 <= scc[u] < n for all u
vector<int> tarjan(const vector<vector<int>>& adj){
    int n = (int)adj.size(), timer = 0, ncomps = 0;
    enum State { unvisited, onStack, visited };
    vector<State> state(n, unvisited);
    vector<int> low(n), id(n), scc(n), stk;
    auto dfs = [&](auto&& dfs, int u) -> void {
        low[u] = id[u] = timer++;
        stk.push_back(u);
        state[u] = onStack;
        for(int v : adj[u]){
            if(state[v] == unvisited) dfs(dfs, v);
            if(state[v] == onStack) low[u] = min(low[u], low[v]);
        }
        if(low[u] == id[u]){
            do{
                int v = stk.back();
                stk.pop_back();
                state[v] = visited;
                scc[v] = ncomps;
            }while(!stk.empty() && id[stk.back()] >= id[u]);
            ++ncomps;
        }
    };
    for(int u = 0; u < n; ++u){
        if(state[u] == unvisited) dfs(dfs, u);
    }
    return scc;
}
