/**
 * Try minimum spanning tree. In this case, Kruskal Algo works better.
 */

#include <iostream>
#include <queue>

#define N 100001

using namespace std;

struct Tunnel {
    int u;
    int v;
    int w;
    Tunnel(int uu, int vv, int ww) {
        u = uu, v = vv, w = ww;
    }
    bool operator < (Tunnel t) const {
        return w > t.w;
    }
};

int uf[N];
priority_queue<Tunnel> q;

int find(int u)
{
    int i;
    for (i = u; i != uf[i]; i = uf[i]);
    while (u != i) {
        int temp = uf[u];
        uf[u] = i;
        u = temp;
    }
    return i;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        uf[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        q.push(Tunnel(u, v, w));
    }
    int min;
    while (!q.empty()) {
        Tunnel t = q.top();
        q.pop();
        int u = find(t.u);
        int v = find(t.v);
        if (u != v) {
            uf[u] = v;
            if (find(1) == find(n)) {
                cout << t.w << endl;
                break;
            }
        }
    }
    return 0;
}
