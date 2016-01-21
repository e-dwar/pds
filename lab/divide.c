#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
divide (int n, int d, int *slices)
{
    int rem = n % d;
    int div = n / d;
    while (d--) {
        slices[d] = div + (
            rem && rem-- && 1
        );
    }
}

int
main (int argc, char *argv[])
{
    int i;
    char *s = argv[1];
    int l = strlen(s);
    int d = atoi(argv[2]);
    int *slices = malloc(sizeof(int) * d);
    divide(l, d, slices);
    printf("string length = %d\n", l);
    printf("slices = [ ");
    for (i = 0; i < d; i++) {
        printf("%d ", slices[i]);
    }
    puts("]");
    free(slices);
    return 0;
}
