#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Router {
    int x;
    int y;
    int k;
    bool addi;
    int cost;
    bool visited;
    Router(int x, int y, bool addi) {
        this->x = x;
        this->y = y;
        this->addi = addi;
        this->k = 0;
        this->cost = INT_MAX;
        this->visited = false;
    }
};

int main()
{
    int n, m, k, r;
    cin >> n >> m >> k >> r;
    int x, y;
    vector<Router> routers;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        Router r(x, y, false);
        routers.push_back(r);
    }
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        Router r(x, y, true);
        routers.push_back(r);
    }
    Router *rt = &routers[0];
    rt->cost = 0;
    long long r_sq = r * (long long) r;
    for (int c = m + n; c > 0; c--) {
        rt->visited = true;
        Router *next = &routers[1];
        for (auto it = routers.begin(); it != routers.end(); it++) {
            long long dx = it->x - rt->x;
            long long dy = it->y - rt->y;
            if (!it->visited && it->k <= k && dx * dx + dy * dy <= r_sq) {
                int ncost = rt->cost + 1;
                if (ncost < it->cost) {
                    it->cost = ncost;
                    it->k = rt->k + (it->addi ? 1 : 0);
                } else if (ncost == it->cost && rt->k < it->k) {
                    it->k = rt->k + (it->addi ? 1 : 0);
                }
            }
            if (!it->visited && it->cost < next->cost) {
                next = &(*it);
            }
        }
        rt = next;
        if (rt->x == routers[1].x && rt->y == routers[1].y) {
            break;
        }
    }
    cout << routers[1].cost - 1 << endl;
    return 0;
}
