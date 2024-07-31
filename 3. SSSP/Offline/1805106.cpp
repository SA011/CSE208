#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void printPath(vector<int> &par, int d, int cost){
    if(cost == INF){
        cout << "The destination is unreachable from the source" << endl;
        return;
    }
    cout << "Shortest path cost: " << cost << endl;
    vector<int> path;
    while(d != -1)path.push_back(d), d = par[d];
    
    for(int i = path.size() - 1; i >= 0; i--){
        cout << path[i];
        if(i)cout << " -> ";
    }
    cout << endl;
    return;
    
}
void dijkstra(vector<vector<pair<int, int>>> &adj, int s, int d){
    int n = adj.size();
    vector<int> dis(n, INF), par(n, -1);
    dis[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, 0));
    
    while(!pq.empty()){
        pair<int, int> u = pq.top();
        pq.pop();
        if(dis[u.second] < u.first)continue;
        for(pair<int, int> v : adj[u.second]){
            if(dis[v.first] > v.second + u.first){
                dis[v.first] = v.second + u.first;
                par[v.first] = u.second;
                pq.push(make_pair(dis[v.first], v.first));
            }
        }
    }
    
    printPath(par, d, dis[d]);
}

void bellmanFord(int n, vector<tuple<int, int, int>> &ed, int s, int d){
    vector<int> dis(n, INF), par(n, -1);
    dis[0] = 0;
    for(int i = 0; i < n - 1; i++){
        for(tuple<int, int, int> x : ed){
            int u, v, w;
            tie(u, v, w) = x;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                par[v] = u;
            }
        }
    }
    for(tuple<int, int, int> x : ed){
        int u, v, w;
        tie(u, v, w) = x;
        if(dis[u] + w < dis[v]){
            cout << "The graph contains a negative cycle" << endl;
            return;
        }
    }
    cout << "The graph does not contain a negative cycle" << endl;
    printPath(par, d, dis[d]);
    
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    vector<tuple<int, int, int>> ed;
    bool neg = 0;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        if(w < 0)neg = 1;
        adj[u].emplace_back(v, w);
        ed.emplace_back(u, v, w);
    }
    int s, d;
    cin >> s >> d;
    if(neg)bellmanFord(n, ed, s, d);
    else dijkstra(adj, s, d);
}
