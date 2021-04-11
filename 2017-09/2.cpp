#include <iostream>
#include <queue>

#define N 1001

using namespace std;

struct Event {
    int num;
    int take;
    int time;
    Event(int nm, int tk, int tm) {
        num = nm, take = tk, time = tm;
    }
    bool operator<(Event const &e) const {
        if (e.time == time) {
            if (e.take == take) {
                return e.num < num;
            }
            return e.take < take;
        }
        return e.time < time;
    }
};


int keybox[N];

int main()
{
    int n, k;
    cin >> n >> k;
    priority_queue<Event> q;
    for (int i = 1; i <= n; i++) {
        keybox[i] = i;
    }
    for (int i = 0; i < k; i++) {
        int w, s, c;
        cin >> w >> s >> c;
        q.push(Event(w, 1, s));
        q.push(Event(w, 0, s + c));
    }
    while (!q.empty()) {
        Event e = q.top();
        q.pop();
        if (e.take) {
            for (int i = 1; i <= n; i++) {
                if (keybox[i] == e.num) {
                    keybox[i] = -1;
                    break;
                }
            }
        } else {
            for (int i = 1; i <= n; i++) {
                if (keybox[i] == -1) {
                    keybox[i] = e.num;
                    break;
                }
            }
        }
        // printf("Time %d, key %d, take %d\n", e.time, e.num, e.take);
        // for (int i = 1; i <= n; i++) {
        //     printf("%d ", keybox[i]);
        // }
        // printf("\n");
    }
    for (int i = 1; i <= n; i++) {
        cout << keybox[i] << ' ';
    }
    cout << endl;
    return 0;
}
