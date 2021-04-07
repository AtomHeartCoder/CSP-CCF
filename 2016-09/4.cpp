#include <iostream>
#include <queue>
#include <vector>

#define N 10001
#define MAX_INT ((~0u) >> 1)

using namespace std;

struct Rail {
    int u;
    int w;
    Rail(int uu, int ww) {
        u = uu, w = ww;
    }
};

struct City {
    int n;
    int cost;
    City(int nn, int cc) {
        n = nn, cost = cc;
    }
    bool operator<(const City c) const {
        return cost > c.cost;
    }
};

vector<Rail> cities[N];
priority_queue<City> unvisited;
int cost[N];
int weight[N];
bool visited[N];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cost[i] = MAX_INT;
        weight[i] = MAX_INT;
        visited[i] = false;
    }
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        cities[a].push_back(Rail(b, c));
        cities[b].push_back(Rail(a, c));
    }
    cost[1] = 0;
    weight[1] = 0;
    unvisited.push(City(1, 0));
    while (!unvisited.empty()) {
        City c = unvisited.top();
        unvisited.pop();
        int u = c.n;
        if (visited[u]) { continue; }
        visited[u] = true;
        for (int i = 0; i < cities[u].size(); i++) {
            Rail r = cities[u][i];
            if (visited[r.u]) { continue; }
            int newcost = c.cost + r.w;
            if (newcost < cost[r.u]) {
                cost[r.u] = newcost;
                weight[r.u] = r.w;
                unvisited.push(City(r.u, newcost));
            } else if (newcost == cost[r.u]) { // this make sure the spanning tree is shortest
                if (r.w < weight[r.u]) {
                    weight[r.u] = r.w;
                }
            }
        }
    }
    int cost = 0;
    for (int i = 2; i <= n; i++) {
        cost += weight[i];
    }
    cout << cost << endl;
    return 0;
}
