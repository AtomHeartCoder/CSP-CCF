#include <stdio.h>
#include <list>

struct gate {
    std::list input;
    int func();

};

int main(void)
{
    int Q;
    scanf("%d", &Q);
    for (int q = 0; q < Q; q++) {
        int M, N;
        scanf("%d%d", &M, &N);
        int *input = (int *) malloc(M * sizeof(int));
        int *gate = (int *) malloc(N * sizeof(int));
        
        for (int 





    }

    return 0;
}
