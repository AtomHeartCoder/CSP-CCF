// Focus on operator "*"! Use "long long" type in every "*" operation!

#include <iostream>
#include <queue>
#include <vector>

#define N       501
#define INF     (~0u >> 2)
#define SQR(x)  ((x) * (x))

using namespace std;

struct Edge {
    int v;
    long long w;        // LONG LONG!
    int t;
    Edge(int vv, int ww, int tt) {
        v = vv, w = ww, t = tt;
    }
};

struct Cross {
    int u;
    int type;
    long long maincost = INF;
    long long sidecost = INF;
    long long sidelen = 0;
    bool visited = false;
    vector<Edge> to;
    long long cost() {
        return maincost <= sidecost ? maincost : sidecost;
    }
} C[N];

struct IQC {
    int u;
    IQC(int uu) { u = uu; }
    bool operator<(const IQC c) const {
        return C[u].cost() > C[c.u].cost();
    }
};

priority_queue<IQC> q;

bool relax(Cross &c, Edge &e)
{
    long long cost;
    if (e.t) {
        long long sidecost = c.cost() - SQR(c.sidelen) + SQR(c.sidelen + e.w);
        long long maincost = c.maincost + SQR(e.w);
        bool takeMain = maincost <= sidecost; // Even though maincost may be bigger than sidecost at u, but things might change if we pass e.
        cost = takeMain ? maincost : sidecost;
        if (cost < C[e.v].cost()) {
            C[e.v].sidecost = cost;
            C[e.v].type = 1;
            C[e.v].sidelen = takeMain ? e.w : c.sidelen + e.w;
            return true;
        }
    } else {
        cost = c.cost() + e.w;
        if (cost < C[e.v].maincost) {
            C[e.v].maincost = cost;
        }
        if (cost <= C[e.v].cost()) {
            C[e.v].maincost = cost;
            C[e.v].sidelen = 0;
            C[e.v].type = 0;
            return true;
        }
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        C[i].u = i;
    }
    for (int i = 0; i < m; i++) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        C[a].to.push_back(Edge(b, c, t));
        C[b].to.push_back(Edge(a, c, t));
    }
    C[1].maincost = C[1].sidecost = C[1].sidelen = C[1].type = 0;
    q.push(IQC(1));
    while (!q.empty()) {    // Dijkstra
        int u = q.top().u;
        q.pop();
        if (C[u].visited) { continue; }
        C[u].visited = true;
        for (auto it = C[u].to.begin(); it != C[u].to.end(); it++) {
            if (!C[it->v].visited && relax(C[u], *it)) {
                q.push(IQC(it->v));
            }
        }
    }
    cout << C[n].cost() << endl;
    return 0;
}
