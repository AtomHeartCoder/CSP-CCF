#include <iostream>
#include <deque>

#define N 10001

using namespace std;

int G[N][N] = {0};
deque<int> stack;
int n, m;

int go(int u)
{
    if (G[u][0] != 0) {
        for (int v = 1; v <= n; v++) {
            if (G[u][v]) {
                stack.push_back(v);
                G[u][v] = G[v][u] = 0;
                G[u][0]--;
                G[v][0]--;
                if (--m == 0) {
                    return 0;
                }
                if (go(v) == 0) {
                    return 0;
                }
                stack.pop_back();
                G[u][v] = G[v][u] = 1;
                G[u][0]++;
                G[v][0]++;
                m++;
            }
        }
    }
    return -1;
}

int main()
{
    int u, v;
    int even = 0;
    cin >> n >> m;
    for (int i = m; i > 0; i--) {
        cin >> u >> v;
        G[u][v] = G[v][u] = 1;
        even += (++G[u][0] % 2) ? 1 : -1;
        even += (++G[v][0] % 2) ? 1 : -1;
    }
    if ((even != 0 && even != 2) || (even == 2 && G[1][0] % 2)) {
        cout << -1 << endl;
        return 0;
    }
    u = 1;
    stack.push_back(u);
    if (go(u) == -1) {
        cout << -1 << endl;
    } else {
        while (!stack.empty()) {
            cout << stack.front() << ' ';
            stack.pop_front();
        }
        cout << endl;
    }
    return 0;
}
