/**
 * Lesson!
 * Changes of the element get from a queue will not affect the
 * corresponding element in the queue!
 * 
 * I am confused by STL, I don't know whether it works with revising
 * references type that gets from the STL containers.
 */

#include <iostream>
#include <queue>
#include <vector>

#define N 10001

using namespace std;

struct Rail {
    int u;
    int w;
    Rail(int uu, int ww) {
        u = uu, w = ww;
    }
};

struct City {
    int num;
    int weight;
    int cost;
    bool visited;
    vector<Rail> to;
} cities[N];

struct cmp {
    bool operator()(int c1, int c2) {
        return cities[c1].cost > cities[c2].cost;
    }
};

priority_queue<int, vector<int>, cmp> unvisited;

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cities[i].num = i;
        cities[i].cost = ~(0u) >> 1;
        cities[i].weight = ~(0u) >> 1;;
        cities[i].visited = false;
    }
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        cities[a].to.push_back(Rail(b, c));
        cities[b].to.push_back(Rail(a, c));
    }
    cities[1].cost = 0;
    cities[1].weight = 0;
    unvisited.push(1);
    while (!unvisited.empty()) {
        City &c = cities[unvisited.top()];
        unvisited.pop();
        if (c.visited) { continue; }
        c.visited = true;
        for (auto it = c.to.begin(); it != c.to.end(); it++) {
            City &cc = cities[it->u];
            if (cc.visited) { continue; }
            int newcost = c.cost + it->w;
            if (newcost < cc.cost) {
                cc.cost = newcost;
                cc.weight = it->w;
                unvisited.push(it->u);
            } else if (newcost == cc.cost) { // this make sure the spanning tree is shortest
                if (it->w < cc.weight) {
                    cc.weight = it->w;
                }
            }
        }
    }
    int cost = 0;
    for (int i = 2; i <= n; i++) {
        cost += cities[i].weight;
    }
    cout << cost << endl;
    return 0;
}
