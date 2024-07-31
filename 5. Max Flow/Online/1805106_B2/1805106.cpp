#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

struct edge{
    int cap, flow, dest, src;
    edge(int s, int d, int c){
        src = s;
        cap = c;
        dest = d;
        flow = 0;
    }
};

struct MaxFlow{
    int n, s, t;
    vector<vector<int>> adj;
    vector<edge> ed;

    MaxFlow(int _n){
        n = _n;
        adj.resize(n);
    }

    void addEdge(int u, int v, int cap){
        adj[u].push_back(ed.size());
        ed.push_back(edge(u, v, cap));

        adj[v].push_back(ed.size());
        ed.push_back(edge(v, u, 0));
    }
    int bfs(){
        queue<int> q;
        q.push(s);
        vector<int> par(n, -2);
        par[s] = -1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int x : adj[u]){
                if(ed[x].cap > ed[x].flow && par[ed[x].dest] == -2){
                    q.push(ed[x].dest);
                    par[ed[x].dest] = x;
                }
            }
        }

        if(par[t] == -2)return 0;

        int fl = 1e9;
        int p = t;
        while(par[p] != -1){
            int l = par[p];
            fl = min(ed[l].cap - ed[l].flow, fl);
            p = ed[l ^ 1].dest;
        }


        p = t;
        while(par[p] != -1){
            int l = par[p];
            ed[l].flow += fl;
            ed[l ^ 1].flow -= fl;
            p = ed[l ^ 1].dest;
        }

        return fl;

    }
    int maxFlow(){
        int ans = 0, f;
        while(f = bfs())
            ans += f;
        return ans;
    }
};

const int INF = 1e9;

int main(){
    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    MaxFlow f(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        f.addEdge(u, v, w);
    }

    cin >> f.s >> f.t;

    cout << "Maximum flow: " << f.maxFlow() << endl;
    cout << "Edges of the mincut: " << endl;
    for(int i = 0; i < 2 * m; i += 2){
        if(f.ed[i].cap == f.ed[i].flow){
            cout << f.ed[i].src << " -> " << f.ed[i].dest << " (Capacity: " << f.ed[i].cap << ")" << endl;
        }
    }
}
