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
void dijkstra(vector<int> &cost, vector<vector<pair<int, int>>> &adj, int s, int d){
    int n = adj.size();
    vector<int> dis(n, INF), par(n, -1);
    dis[s] = cost[s];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(dis[s], s));

    while(!pq.empty()){
        pair<int, int> u = pq.top();
        pq.pop();
        if(dis[u.second] < u.first)continue;
        for(pair<int, int> v : adj[u.second]){
            if(dis[v.first] > v.second + u.first + cost[v.first]){
                dis[v.first] = v.second + u.first + cost[v.first];
                par[v.first] = u.second;
                pq.push(make_pair(dis[v.first], v.first));
            }
        }
    }

    printPath(par, d, dis[d]);
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<int> cost(n);
    for(int i = 0; i < n; i++){
        int u, c;
        cin >> u >> c;
        cost[u] = c;
    }
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    int s, d;
    cin >> s >> d;
    dijkstra(cost, adj, s, d);
}
