#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<vector<int>> rev;
vector<int> vis, ts;

void dfs(int ind){
	vis[ind] = 1;
	for(auto x : adj[ind]){
		if(!vis[x])dfs(x);
	}
	
	ts.push_back(ind);
}

void dfs2(int ind, vector<int> &s){
	vis[ind] = 1;
	s.push_back(ind);
	for(auto x : rev[ind]){
		if(!vis[x])dfs2(x, s);
	}
}

int main(){
	int n, s;
	cin >> n >> s;
	adj.resize(n + 1);
	rev.resize(n + 1);
	
	for(int i = 0; i < s; i++){
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		rev[y].push_back(x);
	}
	
	//Toposort
	vis.resize(n + 1);
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	reverse(ts.begin(), ts.end());
	//reverse dfs
	
	vis.assign(n + 1, 0);
	vector<vector<int>> ans;
	for(auto x : ts){
		if(!vis[x]){
			ans.emplace_back();
			dfs2(x, ans.back());
			
			if(ans.back().size() == 1)ans.pop_back();
		}
	}
	
	
	for(auto x : ans){
		sort(x.begin(), x.end());
		for(auto y : x)cout << y << ' ';
		cout << endl;
	}
}

