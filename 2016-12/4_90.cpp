/**
 * A top-down approach
 * Exceed memory limit! Try a down-top way without recursion.
 * 
 * Solution of this problem
 * We can image that all the words encoded by 0-1 strings form a tree like:
 * 
 *                            X    --- depth 0
 *                           / \
 *                          0   1  --- depth 1
 *                         / \
 *                        0   1    --- depth 2
 * 
 * Every leaf, traced from the root, represents a word. All the leaves counted
 * from left to right exactly satisfy the dictionary order. Besides, we regard
 * the depth of the leaves as their weight. Therefore, our problem turns into
 * resolve the minimun sum of all leaves' weight. Then we dp it!
 */

#include <iostream>

#define N 10001

using namespace std;

int t[N];
int sum[N][N] = {0};
int costs[N][N] = {0};

int cost(int a, int b)
{
    if (costs[a][b]) {
        return costs[a][b];
    }
    if (a == b) {
        return costs[a][b] = t[a];
    }
    int min = (~0u) >> 1;
    for (int i = a; i < b; i++) {
        int res = cost(a, i) + cost(i + 1, b);
        if (res < min) {
            min = res;
        }
    }
    return costs[a][b] = min + sum[a][b];   // the sum means the cost of the depth grow
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i][i] = t[i];
        for (int j = i - 1; j > 0; j--) {
            sum[j][i] = sum[j][i - 1] + t[i];
        }
    }
    int min = (~0u) >> 1;
    for (int i = 1; i < n; i++) {
        int res = cost(1, i) + cost(i + 1, n);
        if (res < min) {
            min = res;
        }
    }
    cout << min << endl;
    return 0;
}
