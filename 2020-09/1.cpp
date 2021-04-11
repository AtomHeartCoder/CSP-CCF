#include <iostream>
#include <queue>

#define SQR(x) ((x) * (x))

using namespace std;

struct IQNode {
    int num;
    int dis;
    IQNode(int n, int d) {
        num = n;
        dis = d;
    }
    bool operator<(IQNode const node) const {
        bool equal = dis == node.dis;
        return equal ? num > node.num : dis > node.dis;
    }
};

priority_queue<IQNode> q;

int main()
{
    int n, x, y;
    cin >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        int xx, yy;
        cin >> xx >> yy;
        q.push(IQNode(i, SQR(xx - x) + SQR(yy - y)));
    }
    for (int i = 0; i < 3; i++) {
        cout << q.top().num << endl;
        q.pop();
    }
    return 0;
}
