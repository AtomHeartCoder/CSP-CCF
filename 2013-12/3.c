#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    short min[1000][1000];
    int n, max = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%hd", &min[i][i]);
        for (int j = 0; j < i; j++) {
            min[j][i] = min[j][i - 1] < min[i][i] ? min[j][i - 1] : min[i][i];
            int s = min[j][i] * (i - j + 1);
            if (s > max) {
                max = s;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
