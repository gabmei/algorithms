template<typename Cap, typename Cost>
struct MinCostMaxFlow{
  const Cost INF = numeric_limits<Cost>::max();
  struct Edge {
    int to, next;
    Cap cap, flow;
    Cost cost;
    Edge(int to, int next, Cap cap, Cost cost) : to(to), next(next), cap(cap), flow(0), cost(cost) {}
    Cap res() const { return cap - flow; }
  };
  int m = 0, n;
  vector<Edge> edges;
  vector<int> first;
  vector<Cap> neck;
  vector<Cost> dist, pot;
  vector<int> from;
  vector<bool> inq;
  queue<int> q;
  MinCostMaxFlow(int n) : n(n), first(n, -1), neck(n), pot(n) {}
  void add_edge(int u, int v, Cap cap, Cost cost) {
    if(u != v) {
      edges.emplace_back(v, first[u], cap, cost);
      edges.emplace_back(u, first[v], 0, -cost);
      first[u] = m++;
      first[v] = m++;
    }	
  }
  bool spfa(int s, int t) {
    //calculate initial potential, pot[u] = dist(s, u)
    dist.assign(n, INF);
    from.assign(n, -1);
    inq.assign(n, false);
    neck[s] = numeric_limits<Cap>::max();
    dist[s] = 0;
    q.push(s);
    while(!q.empty()) {
      auto u = q.front();
      q.pop();
      inq[u] = false;
      for(int id = first[u]; id != -1; id = edges[id].next) {
        auto e = edges[id];
        Cost w = e.cost + pot[u] - pot[e.to];
        if(e.res() > 0 && dist[e.to] > dist[u] + w) {
          from[e.to] = id;
          dist[e.to] = dist[u] + w;
          neck[e.to] = min(neck[u], e.res());
          if(!inq[e.to]) {
            inq[e.to] = true;
            q.push(e.to);
          }
        }
      }
    }
    return dist[t] < INF;
  }
  bool dijkstra(int s, int t) {
    dist.assign(n, INF);
    from.assign(n, -1);
    neck[s] = numeric_limits<Cap>::max();
    using ii = pair<Cost, int>;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({dist[s] = 0, s});
    while(!pq.empty()) {
      auto [d_u, u] = pq.top();
      pq.pop();
      if(dist[u] != d_u) continue;
      for(int id = first[u]; id != -1; id = edges[id].next) {
        auto e = edges[id];
        Cost w = e.cost + pot[u] - pot[e.to];
        if(e.res() > 0 && dist[e.to] > dist[u] + w) {
          from[e.to] = id;
          pq.push({dist[e.to] = dist[u] + w, e.to});
          neck[e.to] = min(neck[u], e.res());
        }
      }
    }
    return dist[t] < INF;
  }
  pair<Cap, Cost> min_cost_max_flow(int s, int t, Cap k = numeric_limits<Cap>::max()) {
    // k : maximum flow allowed
    Cap flow = 0;
    Cost cost = 0;
    // in case of negative cost edges, use spfa + fix_pot
    if(!spfa(s, t)) return {flow, cost};
    fix_pot();
    // if graph is dense, change dijkstra to spfa
    while(flow < k && dijkstra(s, t)) {
      Cap amt = min(neck[t], Cap(k - flow));
      for(int v = t; v != s; v = edges[from[v] ^ 1].to) {
        cost += edges[from[v]].cost * amt;
        edges[from[v]].flow += amt;
        edges[from[v] ^ 1].flow -= amt;
      }
      flow += amt;
      fix_pot();
    }
    return {flow, cost};
  }
  void fix_pot() {
    for(int u = 0; u < n; ++u) {
      if(dist[u] < INF) {
        pot[u] += dist[u];
      }
    }
  }
};
