#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
    int i = 0, j = 0;
    switch (fork()) {
        case -1: exit(EXIT_FAILURE);
        case 0: 
            while (j < 10) {
                j++;
                sleep(1);
                printf("fils ");
                fflush(stdout);
            }
            printf("fin ");
            fflush(stdout);
            exit(EXIT_SUCCESS);
        default: 
            while(1) {
                i++;
                sleep(1);
                printf("pere ");
                fflush(stdout);
                if (i == 5) {
                    printf("pause ");
                    fflush(stdout);
                    wait(NULL);
                    printf("resume ");
                    fflush(stdout);
                }
            }
    }
    return 0;
}
