#include<bits/stdc++.h>
using namespace std;


bool dfs(int ind, vector<vector<int>> &adj, vector<int> &vis){
    vis[ind] = 1;
    for(int x : adj[ind]){
        if(vis[x] == 1)return true; //backEdge. Cycle detected
        if(vis[x] == 0 && dfs(x, adj, vis))return true;
    }
    vis[ind] = 2;
    return false;
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> vis(n);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    for(int i = 0; i < n; i++){
        if(!vis[i] && dfs(i, adj, vis)){
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
}
