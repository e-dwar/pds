#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

void fail ();
void affiche_lien (const char *);
void parcours_rep (const char *);
void liens_symboliques (const char *);
void build_path (const char *, const char *, char *);
int valid_name (const char *);

int main (int argc, char *argv[]) 
{
    errno = 0;
    if (argc == 1) fail();
    liens_symboliques(argv[1]);
    return 0; 
}

void liens_symboliques (const char *chemin)
{
    struct stat st;
    if (valid_name(chemin)) {
        if (lstat(chemin, &st) == -1) fail();
        if (S_ISDIR(st.st_mode)) parcours_rep(chemin);
        else if (S_ISLNK(st.st_mode)) affiche_lien(chemin);
    }
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

void parcours_rep (const char *chemin)
{
    struct dirent *e;
    char path[PATH_MAX];
    DIR *d = opendir(chemin);
    if (d == NULL) fail();
    while ((e = readdir(d))) {
        build_path(chemin, e->d_name, path);
        liens_symboliques(path);
    }
    if (errno != 0) fail();
    if (closedir(d) == -1) fail();
}

/* fct utilitaires */

void build_path (const char *dirpath, const char *filename, char *fullpath)
{
    int ld = strlen(dirpath);
    int hasSlash = dirpath[ld - 1] == '/';
    int lf = strlen(filename);
    int lp = ld + lf;
    if (!hasSlash) lp += 1;
    assert(lp < PATH_MAX);
    strcpy(fullpath, dirpath);
    if (!hasSlash) strcat(fullpath, "/");
    strcat(fullpath, filename);
}

int valid_name (const char *pathname)
{
    int i = strlen(pathname);
    while (pathname[i] != '/' && i > 0) i--;
    if (strcmp(pathname + i + 1, ".") == 0) return 0;
    else if (strcmp(pathname + i + 1, "..") == 0) return 0;
    else return 1;
}

void fail () 
{
    exit(EXIT_FAILURE);
}


