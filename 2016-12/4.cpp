/**
 * A down-top way without recursion.
 */

#include <iostream>

#define N 10001

using namespace std;

int t[N];
int sum[N][N];
int cost[N][N] = {0};

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        cost[i][i] = sum[i][i] = t[i];
        for (int j = 1; j < i; j++) {
            sum[j][i] = sum[j][i - 1] + t[i];
        }
    }
    for (int scale = 2; scale < n; scale++) {
        int endi = n - scale + 1;
        for (int i = 1; i <= endi; i++) {
            int endj = i + scale - 1;
            int min = (~0u) >> 1;
            for (int j = i; j < endj; j++) {
                int c = cost[i][j] + cost[j + 1][endj];
                if (c < min) { min = c; }
            }
            cost[i][endj] = min + sum[i][endj];
        }
    }
    int min = (~0u) >> 1;
    for (int i = 1; i < n; i++) {
        int c = cost[1][i] + cost[i + 1][n];
        if (c < min) {
            min = c;
        }
    }
    cout << min << endl;
    return 0;
}

