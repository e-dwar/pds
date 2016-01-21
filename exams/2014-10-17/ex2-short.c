#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>

void fail ();
void affiche_lien (const char *);
void liens_symboliques (const char *);

int main (int argc, char *argv[]) 
{
    if (argc == 1) fail();
    liens_symboliques(argv[1]);
    return 0; 
}

void fail () 
{
    exit(EXIT_FAILURE);
}

void liens_symboliques (const char *chemin)
{
    struct stat st;
    if (lstat(chemin, &st) == -1) fail();
    if (S_ISLNK(st.st_mode)) affiche_lien(chemin);
}

void affiche_lien (const char *chemin)
{
    int bytes;
    char buf[PATH_MAX + 1];
    bytes = readlink(chemin, buf, PATH_MAX + 1);
    if (bytes == -1) fail();
    buf[bytes] = '\0';
    printf("%s -> %s\n", chemin, buf);
}


