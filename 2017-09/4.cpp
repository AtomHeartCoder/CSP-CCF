#include <iostream>
#include <vector>
#include <cstring>
#define N 1001

using namespace std;

short connected[N][N];
char visited[N];
vector<int> G[N];

void dfs(int start, int i)
{
	visited[i] = 1;
	for (auto it = G[i].begin(); it != G[i].end(); it++) {
		if (!visited[*it]) {
			connected[start][*it] = 1;
			connected[*it][start] = 1;
			dfs(start, *it);
		}
	}

}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		connected[i][i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);	
		connected[a][b] = 1;
		connected[b][a] = 1;
	}
	for (int i = 1; i <= n; i++) {
		memset(visited, 0, n + 1);
		dfs(i, i);
	}
	int count = 0;
	for (int i = 1; i <= n; i++) {
		bool all = true;
		for (int j = 1; j <= n; j++) {
			if (!connected[i][j]) {
				all = false;
				break;
			}
		}
		if (all) {
			count++;
		}
	}
	cout << count << endl;
	return 0;
}



