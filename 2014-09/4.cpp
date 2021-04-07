#include <iostream>
#include <queue>
#include <utility>

#define N 1002

using namespace std;

int zoom[N][N] = { 0 };

int main()
{
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    for (int i = 1; i <= n; i++) {
        zoom[i][0] = zoom[i][n + 1] = zoom[0][i] = zoom[n + 1][i] = -1;
    }
    queue<pair<int, int>> q;
    int x, y, meal;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        zoom[x][y] = -1;
        q.push(make_pair(x, y));
    }
    q.push(make_pair(-1, -1));
    for (int i = 0; i < k; i++) {
        cin >> x >> y >> meal;
        zoom[x][y] += meal;
    }
    for (int i = 0; i < d; i++) {
        cin >> x >> y;
        zoom[x][y] = -1;
    }
    long long cost = 0;
    int dis = 1;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        if (p.first == -1) {
            if (q.empty()) {
                break;
            }
            q.push(make_pair(-1, -1));
            dis++;
            continue;
        }
        x = p.first, y = p.second;
        static int dx[] = { 0, 0, 1, -1 };
        static int dy[] = { 1, -1, 0, 0 };
        for (int i = 0; i < 4; i++) {
            if (zoom[x + dx[i]][y + dy[i]] >= 0) {
                if (zoom[x + dx[i]][y + dy[i]] > 0) {
                    cost += dis * zoom[x + dx[i]][y + dy[i]];
                }
                zoom[x + dx[i]][y + dy[i]] = -1;
                q.push(make_pair(x + dx[i], y + dy[i]));
            }
        }
    }
    cout << cost << endl;
    return 0;
}
