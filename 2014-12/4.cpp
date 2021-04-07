#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define N_MAX 1000

int uf[N_MAX + 1];

struct edge {
    int a;
    int b;
    int c;
    edge(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

struct cmp {
    bool operator()(edge e1, edge e2) {
        return e1.c > e2.c;
    }
};
priority_queue<edge, vector<edge>, cmp> edges;

int main()
{
    int n, m;
    cin >> n >> m;
    uf[0] = n;
    for (int i = 1; i <= n; i++) {
        uf[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push(edge(a, b, c));
    }
    long long cost = 0;
    while (uf[0] > 1 && !edges.empty()) {
        edge e = edges.top();
        edges.pop();
        int s, t;
        for (s = e.a; s != uf[s]; s = uf[s]);
        for (t = e.b; t != uf[t]; t = uf[t]);
        if (s != t) {
            uf[s] = t;
            cost += e.c;
            uf[0]--;
            for (int x = e.a; x != s; ) {
                int tmp = uf[x];
                uf[x] = s;
                x = tmp;
            }
            for (int x = e.b; x != t; ) {
                int tmp = uf[x];
                uf[x] = t;
                x = tmp;
            }

        }
    }
    cout << cost << endl;
    return 0;
}
