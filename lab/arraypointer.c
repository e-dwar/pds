#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
    int i, n = 4;
    int (*m)[2];
    m = malloc(sizeof(int (*)[2]) * n);
    for (i = 0; i < n; i++) {
        m[i][0] = 'A' + i;
        m[i][1] = 'a' + i;
    }
    for (i = 0; i < n; i++) {
        printf("['%c', '%c'] ", m[i][0], m[i][1]);
    }
    return 0;
}
