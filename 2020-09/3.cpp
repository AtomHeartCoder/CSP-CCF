#include <iostream>
#include <list>
#include <vector>

using namespace std;

int _not(list<int *> l)
{
    int res = *(l.front());
    if (res == -1) { return -1; }
    return !res;
}

int _and(list<int *> l)
{
    int res = 0;
    for (auto it = l.begin(); it != l.end(); it++) {
        if (**it == -1) {
            return -1;
        }
        res &= **it;
    }
    return res;
}

int _or(list<int *> l)
{
    int res = 0;
    for (auto it = l.begin(); it != l.end(); it++) {
        if (**it == -1) {
            return -1;
        }
        res |= **it;
    }
    return res;
}

int _xor(list<int *> l)
{
    int res = 0;
    for (auto it = l.begin(); it != l.end(); it++) {
        if (**it == -1) {
            return -1;
        }
        res ^= **it;
    }
    return res;
}

int nand(list<int *> l)
{
    int res = _and(l);
    return res == -1 ? -1 : !res;
}

int nor(list<int *> l)
{
    int res = _or(l);
    return res == -1 ? -1 : !res;
}

struct gate {
    list<int *> input;
    int func;
    int output() {
        switch (func) {
            case 0: return _not(input);
            case 1: return _and(input);
            case 2: return _or(input);
            case 3: return _xor(input);
            case 4: return nand(input);
            case 5: return nor(input);
        }
        return -1;
    }
};

void go()
{
    int m, n;
    cin >> m >> n;
    vector<int> inputs(m + 1);
    vector<int> outputs(n + 1);
    vector<gate> gates(n + 1);
    for (int i = 1; i <= n; i++) {
        char func[5];
        int k;
        cin >> func >> k;
        switch (func[0]) {
            case 'A':
                gates[i].func = 1;
                break;
            case 'O':
                gates[i].func = 2;
                break;
            case 'X':
                gates[i].func = 3;
                break;
            default:
                if (func[2] == 'T') {
                    gates[i].func = 0;
                } else if (func[2] == 'N') {
                    gates[i].func = 4;
                } else {
                    gates[i].func = 5;
                }
        }
        for (int j = 0; j < k; j++) {
            char out;
            int num;
            cin >> out >> num;
            gates[i].input.push_back(out == 'O' ? &outputs[num] : &inputs[num]);
        }
    }
    int s;
    cin >> s;
    vector<vector<int>> res;
    bool loop = false;
    for (int i = 0; i < s; i++) {
        for (int o = 1; o <= n; o++) {
            outputs[o] = -1;
        }
        for (int j = 1; j <= m; j++) {
            cin >> inputs[j];
        }
        int unknown = n;
        while (!loop && unknown) {
            bool found = false;
            for (int o = 1; o <= n; o++) {          // output() depends on inputs and outputs of other gates.
                if (outputs[o] == -1) {             // If we can't find any gates that all inputs are determined, a loop exists.
                    int res = gates[o].output();
                    if (res != -1) {
                        outputs[o] = res;
                        unknown--;
                        found = true;
                    }
                }
            }
            if (!found) {
                loop = true;
                break;
            }
        }
        res.push_back(vector<int>(outputs));
    }
    for (int i = 0; i < s; i++) {
        int si;
        cin >> si;
        while (si--) {
            int o;
            cin >> o;
            if (!loop)
                cout << res[i][o] << ' ';
        }
        if (!loop)
            cout << endl;
    }
    if (loop) {
        cout << "LOOP" << endl;
    }
}

int main(void)
{
    int Q;
    cin >> Q;
    while (Q--) {
        go();
    }
    return 0;
}
