#include <iostream>
#include <stack>
#include <list>

#define N 10001
#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

struct Vertex {
    int dfn;
    int low;
    bool instack;
    list<int> to;
};

Vertex vs[N];
stack<int> vstack;
int total = 0;
int idx = 0;

void tarjan(int u)
{
    vs[u].dfn = vs[u].low = ++idx;
    vstack.push(u);
    vs[u].instack = true;
    for (list<int>::iterator it = vs[u].to.begin(); it != vs[u].to.end(); it++) {
        int v = *it;
        if (vs[v].dfn == 0) {         // not visited
            tarjan(v);
            vs[u].low = min(vs[u].low, vs[v].low);
        } else if (vs[v].instack) {
            vs[u].low = min(vs[u].low, vs[v].dfn);
        }
    }
    if (vs[u].dfn == vs[u].low) {
        int count = 0;
        int v;
        do {
            v = vstack.top();
            vstack.pop();
            vs[v].instack = false;
            count++;
        } while (u != v);
        if (count > 1) {
            total += count * (count - 1) / 2;
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        vs[i].dfn = 0;
        vs[i].low = 0;
        vs[i].instack = false;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        vs[u].to.push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (vs[i].dfn == 0) {
            tarjan(i);
        }
    }
    cout << total << endl;
    return 0;
}
