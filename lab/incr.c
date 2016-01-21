#include <stdio.h>

int incr (int *i)
{
    return *i = *i + 1;
}

int main ()
{
    int i = 1;
    printf("i = %d\n", i);
    printf("incr(&i) = %d\n", incr(&i));
    printf("i = %d\n", i);
    return 0;
}
