#include <iostream> 
#include <iomanip> 
#include <vector>
#include <queue>
using namespace std;

struct edge{
    int cap, flow, dest;
    edge(int d, int c){
        cap = c;
        dest = d;
        flow = 0;
    }
};

struct MaxFlow{
    int n, s, t;
    vector<vector<int>> adj;
    vector<edge> ed;
    
    MaxFlow(int _n, int _s, int _t){
        n = _n;
        s = _s;
        t = _t;
        adj.resize(n);
    }
    
    void addEdge(int u, int v, int cap){
        adj[u].push_back(ed.size());
        ed.push_back(edge(v, cap));
        
        adj[v].push_back(ed.size());
        ed.push_back(edge(u, 0));
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
    int n;
    cin >> n;
    vector<string> teams(n);
    
    vector<int> w(n), r(n), l(n);
    
    vector<vector<int>> mat(n, vector<int>(n));
    
    int mx = 0;     //max win
    for(int i = 0; i < n; i++){
        cin >> teams[i] >> w[i] >> l[i] >> r[i];
        if(w[mx] < w[i])mx = i;
        for(int j = 0; j < n; j++)cin >> mat[i][j];
    }
    
    vector<pair<int, int>> games;
    int tot = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            games.push_back(make_pair(i, j));
            tot += mat[i][j]; 
        }
    }
    int m = games.size();

    auto print = [&](int elem, vector<int> rsn){
        cout << teams[elem] << " is eliminated." << endl;
        cout << "They can win at most " << w[elem] << " + " << r[elem] << " = " << w[elem] + r[elem] << " games." << endl;
        cout << teams[rsn[0]];
        int k = w[rsn[0]];
        for(int i = 1; i < rsn.size(); i++){
            if(i == rsn.size() - 1)cout << " and ";
            else cout << ", ";
            cout << teams[rsn[i]];
            k += w[rsn[i]];
        }
        
        cout << (rsn.size() == 1 ? " has" : " have") << " won a total of " << k << " games." << endl;
        
        int ech = 0;
        for(int i = 0; i < rsn.size(); i++){
            for(int j = i + 1; j < rsn.size(); j++)ech += mat[rsn[i]][rsn[j]];
        }
        
        cout << "They play each other " << ech << " times." << endl;
        cout << "So on average, each of the teams in this group wins " << ech + k << "/" << rsn.size() << " = " 
            << fixed << setprecision(6) << (double)(ech + k) / rsn.size() << " games." << endl;
        cout << endl;
    };
    
    for(int i = 0; i < n; i++){
        if(w[i] + r[i] < w[mx]){
            print(i, vector<int>(1, mx));
            continue;
        }
        
        MaxFlow f(m + n + 2, 0, m + n + 1);
        
        for(int j = 0; j < n; j++){
            f.addEdge(j + m + 1, n + m + 1, w[i] + r[i] - w[j]);
        }
        
        for(int j = 0; j < m; j++){
            int a = games[j].first, b = games[j].second;
            f.addEdge(0, j + 1, mat[a][b]);
            f.addEdge(j + 1, m + a + 1, INF);
            f.addEdge(j + 1, m + b + 1, INF);
        }
        
        int u = f.maxFlow();
        
        if(u < tot){
            vector<bool> prob(n);
            queue<int> q;
            for(int x : f.adj[0]){
                if(f.ed[x].cap > f.ed[x].flow){
                    int d = f.ed[x].dest - 1;
                    q.push(games[d].first);
                    q.push(games[d].second);
                    prob[games[d].second] = 1;
                    prob[games[d].first] = 1;
                    break;
                }
            }
            
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int x : f.adj[u + m + 1]){
                    int d = f.ed[x].dest;
                    if(d == n + m + 1)continue;
                    if(f.ed[x].cap > f.ed[x].flow){
                        int a = games[d - 1].first, b = games[d - 1].second;
                        if(!prob[a])q.push(a), prob[a] = 1;
                        if(!prob[b])q.push(b), prob[b] = 1;
                    }
                }
            }
            vector<int> rsn;
            for(int j = 0; j < n; j++)if(prob[j])rsn.push_back(j);
            print(i, rsn);
        }
    }
}
