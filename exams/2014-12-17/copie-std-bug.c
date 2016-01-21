#include <unistd.h>
#include <stdio.h>
#define TAILLE 8

int
main (int argc, char *argv[])
{
    char tampon[TAILLE];
    /* O][I -> O][I */
    /* 1][0 -> 1][0 */
    while (read(0, tampon, TAILLE) > 0) {
        write(1, tampon, TAILLE);
    }
    return 0;
}
