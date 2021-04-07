/**
 * Note
 * 采用 BFS，则遍历深度也就代表了时间，是渐增的。对于 t 时刻，BFS 的队列中会包含所有可能的位置。
 * 因此第一次遇到 (n, m) 时，就是最早到达的时刻。需要注意的是，对于某一点，可以在不同的两个时刻
 * 访问，不能排重！
 */

#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define N 101
#define M 101
#define T 300

struct Cell {
    int start = 0;
    int end = 0;
    bool visited[T] = {false};
} table[N][M];

struct Moment {
    int r;
    int c;
    int t;
    Moment(int rr, int cc, int tt) {
        r = rr;
        c = cc;
        t = tt;
    }
};

struct {
    int dr;
    int dc;
} d[] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

queue<Moment> q;

int main()
{
    int n, m, t;
    int r, c, a, b;
    cin >> n >> m >> t;
    while (t--) {
        cin >> r >> c >> a >> b;
        table[r][c].start = a;
        table[r][c].end = b;
    }
    q.push(Moment(1, 1, 0));
    while (!q.empty()) {
        Moment now = q.front();
        q.pop();
        r = now.r, c = now.c, t = now.t;
        if (r == n && c == m) { break; }
        t++;
        for (int i = 0; i < 4; i++) {
            int x = r + d[i].dr;
            int y = c + d[i].dc;
            bool overboundary = x < 1 || x > n || y < 1 || y > m;
            bool dangerous = t >= table[x][y].start && t <= table[x][y].end;
            if (overboundary || dangerous) {
                continue;
            }
            if (!table[x][y].visited[t]) {
                table[x][y].visited[t] = true;
                q.push(Moment(x, y, t));
            }
            
        }


    }
    cout << t << endl;
    return 0;

}
