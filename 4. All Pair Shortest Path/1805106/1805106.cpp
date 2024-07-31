#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("in.txt", "r", stdin);
	int n, m;
	cin >> n >> m;
	const int INF = 1e9;
	vector<vector<int>> mat(n + 1, vector<int>(n + 1, INF));
	for(int i = 0; i < m; i++){
		int x, y, w;
		cin >> x >> y >> w;
		mat[x][y] = min(mat[x][y], w);
	}
	
	for(int i = 1; i <= n; i++)mat[i][i] = min(mat[i][i], 0);
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int k = 1; k <= n; k++){
				if(mat[j][i] < INF && mat[i][k] < INF)
					mat[j][k] = min(mat[j][k], mat[j][i] + mat[i][k]);
			}
		}
	}
	cout << "Shortest distance matrix\n" << endl;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(mat[i][j] == INF) cout << setw(7) << "INF" << ' ';
			else cout << setw(7) << mat[i][j] << ' ';
		}
		cout << endl;
	}
}
