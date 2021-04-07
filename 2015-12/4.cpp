/* Use 'short' instead of 'int' */

#include <iostream>
#include <deque>
#include <utility>

#define N 10001

using namespace std;

short G[N][N] = {0};
deque<short> path;
int n, m;

// Hierholzer Algo
void go(short u)
{
    for (short v = 1; G[u][0] > 0 && v <= n; v++) {
        if (G[u][v]) {
            G[u][v] = G[v][u] = 0;
            G[u][0]--, G[v][0]--;
            m--;
            go(v);

        }
    }
    if (G[u][0] == 0) {
        path.push_back(u);
    }
}

int main()
{
    short u, v;
    int even = 0;
    cin >> n >> m;
    for (int i = m; i > 0; i--) {
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
        even += (++G[u][0] % 2) ? 1 : -1;
        even += (++G[v][0] % 2) ? 1 : -1;
    }
    if ((even != 0 && even != 2) || (even == 2 && !(G[1][0] % 2))) {
        cout << -1 << endl;
        return 0;
    }
    go(1);
    if (m != 0) {
        cout << -1 << endl;
    } else {
        while (!path.empty()) {
            cout << path.back() << ' ';
            path.pop_back();
        }
        cout << endl;
    }
    return 0;
}
