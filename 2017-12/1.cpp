#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin >> n;
    priority_queue<int> q;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        q.push(a);
    }
    int min = ~0u >> 1;
    int old = q.top();
    q.pop();
    while (!q.empty()) {
        int diff = old - q.top();
        old = q.top();
        q.pop();
        if (diff < min) {
            min = diff;
        }
    }
    cout << min << endl;
    return 0;
}
