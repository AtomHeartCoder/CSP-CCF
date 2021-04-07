#include <stdio.h>

int main(void)
{
    int n, k, t, x_l, y_d, x_r, y_u;
    int pass = 0, remain = 0;
    scanf("%d %d %d %d %d %d %d", &n, &k, &t, &x_l, &y_d, &x_r, &y_u);
    for (int i = 0; i < n; i++) {
        int count = 0;
        int flag = 0;
        for (int j = 0; j < t; j++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x >= x_l && x <= x_r && y >= y_d && y <= y_u) {
                if (!flag) {
                    flag = 1;
                    pass++;
                }
                count++;
                if (count >= k) {
                    flag = 2;
                }
            } else {
                count = 0;
            }
        }
        if (flag == 2) {
            remain++;
        }
    }
    printf("%d\n%d", pass, remain);
    return 0;
}
