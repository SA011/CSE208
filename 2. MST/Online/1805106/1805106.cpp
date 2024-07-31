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


long long int kruskal(vector<tuple<int, int, int>> &edge, vector<pair<int, int>> &takenEdge, int n){
	sort(edge.begin(), edge.end());
	Unionfind un(n);
	long long int ans = 1;
	for(auto x : edge){
        int u, v, w;
        tie(w, u, v) = x;
		if(!un.sameset(u, v)){
			ans *= w;
			takenEdge.emplace_back(u, v);
			un.unionset(u, v);
		}
	}

	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;

	vector<tuple<int, int, int>> edge;

	for(int i = 0; i < m; i++){
		int a, b, d;
		cin >> a >> b >> d;
		edge.emplace_back(d, a, b);
	}
    if(n == 1){
        cout << "Minimum Product : 0" << endl;
        return 0;
    }
	vector<pair<int, int>> kruskalAnswer;
	long long kAns = kruskal(edge, kruskalAnswer, n);

	cout << "Minimum Product : " << kAns << endl;
	cout << "Edges: ";

	for(int i = 0; i < kruskalAnswer.size(); i++){
		cout << kruskalAnswer[i].first << "-" << kruskalAnswer[i].second;
		if(i + 2 < kruskalAnswer.size())cout << ", ";
		else if(i + 1 < kruskalAnswer.size())cout << " and ";
	}
	cout << endl;
}
