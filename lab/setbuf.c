#include <stdio.h>

int main ()
{
    setbuf(stdout, NULL);
    printf("allo");
    sleep(5);
    return 0;
}
