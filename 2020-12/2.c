#include <stdio.h>
#include <stdlib.h>

static inline
int predict(int y, int theta)
{
    return y >= theta;
}

int main(void)
{
    int m;
    scanf("%d", &m);
    struct data {
        int y;
        int result;
    } *min_heap;
    min_heap = (struct data *) malloc(m * sizeof(struct data));

    for (int i = 0; i < m; i++) {
        struct data input;
        scanf("%d%d", &input.y, &input.result);
        

    }
    return 0;
}
