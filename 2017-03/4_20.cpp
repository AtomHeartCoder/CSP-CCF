/**
 * Broke time limit!
 * This algo may be right, but poorly efficient. It searches every path from 1 to n,
 * and deletes the longest tunnel on the path to avoid passing it again (once we go
 * through this tunnel, the cost will not be less than its weight). Besides, if we
 * meet a leaf node (other than n), we delete its only connecting tunnel, because it
 * leads to nowhere.
 */

#include <iostream>
#include <list>
#include <vector>

#define N 100001

using namespace std;

struct Tunnel {
    int v;
    int w;
    Tunnel(int vv, int ww) {
        v = vv;
        w = ww;
    }
};

vector<list<Tunnel>> g(N);
vector<bool> visited(N, false);
vector<int> maxs;
int n;

int search(int u, int max)
{
    if (u == n) {
        maxs.push_back(max);
        return 1;
    }
    visited[u] = true;
    auto it = g[u].begin();
    while (it != g[u].end()) {
        if (visited[it->v]) {
            it++;
            continue;
        }
        int res = search(it->v, it->w > max ? it->w : max);
        if (res == 1) {                     // reach the n'th hub, trace back
            if (it->w > max) {              // trace back to the longest tunnel, delete it and keep searching
                g[it->v].remove_if([u](Tunnel t) { return t.v == u; });
                it = g[u].erase(it);
            } else {                        // not trace back to the longest tunnel, keep tracing
                visited[u] = false;
                return 1;
            }
        } else if (res == -1) {             // return from a leaf, delete the tunnel to avoid later visit
            g[it->v].remove_if([u](Tunnel t) { return t.v == u; });
            it = g[u].erase(it);
        } else {                            // res == 0, this situation may be a circle detection, search the next neighbor
            it++;
        }
    }
    visited[u] = false;
    if (g[u].size() == 1) {                 // now u becomes a leaf, notify its last node to delete the tunnel to it
        return -1;
    }
    return 0;                               // maybe form a circle
}

// dfs
int main()
{
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back(Tunnel(b, c));
        g[b].push_back(Tunnel(a, c));
    }
    search(1, 0);
    int min = (~0u) >> 1;
    for (auto it = maxs.begin(); it != maxs.end(); it++) {
        if (*it < min) {
            min = *it;
        }
    }
    cout << min << endl;
    return 0;
}
