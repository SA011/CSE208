#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include <queue>
#include <assert.h>
#include <algorithm>

using namespace std;


class Unionfind{
public:
    vector<int> p, rnk;
    int n;
    Unionfind(int _n) : n(_n) { 
        p.assign(n, 0), rnk.assign(n, 1); 
        for(int i = 0; i < n; i++)p[i] = i;
    }
    int findset(int i){return p[i] = (p[i] == i) ? i : findset(p[i]);}
    bool sameset(int i, int j){return findset(i) == findset(j);}
    void unionset(int i, int j) {
        int x = findset(i), y = findset(j);
        if(x != y){
            if(rnk[x] > rnk[y]) p[y] = x;
            else p[x] = y, rnk[y] += (rnk[x] == rnk[y]);
        }
    }
};


double kruskal(vector<tuple<double, int, int>> &edge, vector<pair<int, int>> &takenEdge, int n){
	sort(edge.begin(), edge.end());
	Unionfind un(n);
	double ans = 0;
	for(auto [w, u, v] : edge){
		if(!un.sameset(u, v)){
			ans += w;
			takenEdge.emplace_back(u, v);
			un.unionset(u, v);
		}
	}
	
	return ans;
}


double prim(vector<vector<pair<int, double>>> &adj, vector<pair<int, int>> &takenEdge, int n){
	vector<bool> vis(n);
	
	priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<tuple<double, int, int>>> pq;
	pq.push(make_tuple(0, -1, 0));
	double ans = 0;
	while(!pq.empty()){
		auto [w, a, b] = pq.top();
		pq.pop();
		if(vis[b])continue;
		ans += w;
		vis[b] = 1;
		if(a != -1)takenEdge.emplace_back(a, b);
		
		for(auto [c, w] : adj[b]){
			if(!vis[c])pq.push(make_tuple(w, b, c));
		}
	}
	
	return ans;
}


int main(){	
	
	freopen("mst.in", "r", stdin);
	
	int n, m;
	cin >> n >> m;
	
	vector<vector<pair<int, double>>> adj(n); //For Prim
	vector<tuple<double, int, int>> edge; //For Kruskal
	
	for(int i = 0; i < m; i++){
		int a, b;
		double d;
		cin >> a >> b >> d;
		edge.emplace_back(d, a, b);
		adj[a].emplace_back(b, d);
		adj[b].emplace_back(a, d);
	}
	
	vector<pair<int, int>> kruskalAnswer, primAnswer;
	double kAns, pAns;
	pAns = prim(adj, primAnswer, n);
	kAns = kruskal(edge, kruskalAnswer, n);
	
	assert(pAns == kAns);
	
	cout << "Cost of the minimum spanning tree : " << fixed << setprecision(10) << kAns << endl;
	cout << "List of edges selected by Prim's:{";
	
	for(int i = 0; i < primAnswer.size(); i++){
		if(i)cout << ',';
		cout << "(" << primAnswer[i].first << "," << primAnswer[i].second << ")";
	}
	cout << "}\n";
	
	cout << "List of edges selected by Kruskal's:{";
	
	for(int i = 0; i < kruskalAnswer.size(); i++){
		if(i)cout << ',';
		cout << "(" << kruskalAnswer[i].first << "," << kruskalAnswer[i].second << ")";
	}
	cout << "}\n";
}
