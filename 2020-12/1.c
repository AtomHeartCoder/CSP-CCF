#include <stdio.h>

int main(void)
{
    int n, sum, score, w;
    scanf("%d", &n);
    sum = 0;
    while (n--) {
        scanf("%d%d", &w, &score);
        sum += w * score;
    }
    printf("%d", sum >= 0 ? sum : 0);
    return 0;
}
