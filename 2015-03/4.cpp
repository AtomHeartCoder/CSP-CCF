#include <iostream>
#include <utility>

using namespace std;

#define N 10001
#define M 10001

struct Node {
    int parent;
    pair<int, int> max1;
    pair<int, int> max2;
    Node() {;}
    Node(int p) {
        parent = p;
        max1 = make_pair(0, 0);
        max2 = make_pair(0, 0);
    }
    bool check(int child, int depth) {
        if (depth > max1.second) {
            if (child == max1.first) {
                max1.second = depth;
            } else {
                max2 = max1;
                max1.first = child;
                max1.second = depth;
            }
            return true;
        }
        if (depth > max2.second) {
            max2.first = child;
            max2.second = depth;
        }
        return false;
    }
};

Node nodes[N];

void update(int id, int child, int depth)
{
    if (id == 0) { return; }
    if (nodes[id].check(child, depth)) {
        update(nodes[id].parent, id, nodes[id].max1.second + 1);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    nodes[1] = Node(0);
    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        nodes[i] = Node(parent);
        update(parent, i, 1);
    }
    for (int i = 1; i <= m; i++) {
        int parent;
        cin >> parent;
        update(parent, i + n, 1);
    }
    int max = 0;
    for (int i = 1; i <= n; i++) {
        int cost = nodes[i].max1.second + nodes[i].max2.second;
        if (cost > max) {
            max = cost;
        }
    }
    cout << max << endl;
    return 0;
}
