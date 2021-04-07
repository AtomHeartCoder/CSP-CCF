/**
 * I believe we can learn something from the Dijkstra Algorithm. Assuming we do
 * so, we record the longest tunnel on the way of searching instead of the less
 * cost for every node this time. It's like the 20-score-algo, but, we do something
 * different -- recording. We don't delete tunnels to avoid redundant visits, but
 * we record the value we want for the redundant visits. Don't talk too much,
 * let's code and find out whether I solve it right!
 * 
 * This may be an extension of Dijkstra Algorithm. Besides the "shortest", if we
 * name a feature, like "path with shortest length" or "path with minimum longest
 * edge", just regard the feature as f(). For a node u and one of its neighbors,
 * maybe v, if we can infer the new f(v) by conbining f(u) and (u, v), we might be
 * able to apply the Dijkstra Algorithm.
 */

#include <iostream>
#include <queue>
#include <vector>

#define N 100001

using namespace std;

struct Tunnel {
    int u;
    int w;
    Tunnel(int uu, int ww) {
        u = uu, w = ww;
    }
};

struct Hub {
    int u;
    int cost;
    Hub(int uu, int cc) {
        u = uu, cost = cc;
    }
    bool operator<(const Hub h) const {
        return cost > h.cost;
    }
};

vector<Tunnel> hubs[N];
priority_queue<Hub> unvisited;
vector<int> cost(N, (~0u) >> 1);
vector<bool> visited(N, false);

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        hubs[a].push_back(Tunnel(b, c));
        hubs[b].push_back(Tunnel(a, c));
    }
    cost[1] = 0;
    unvisited.push(Hub(1, 0));
    while (!unvisited.empty()) {
        Hub h = unvisited.top();
        unvisited.pop();
        if (visited[h.u]) { continue; }
        visited[h.u] = true;
        for (auto it = hubs[h.u].begin(); it != hubs[h.u].end(); it++) {
            if (visited[it->u]) { continue; }
            int c = cost[h.u] > it->w ? cost[h.u] : it->w;
            if (c < cost[it->u]) {
                cost[it->u] = c;
                unvisited.push(Hub(it->u, c));
            }
        }
    }
    cout << cost[n] << endl;
    return 0;
}
