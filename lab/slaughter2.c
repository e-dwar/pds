/**
 * Les processus fils impriment un message toutes les 4 secondes.
 * Le processus père tue un fils toutes les 4 secondes et se
 * donne la mort quand tous ses fils sont morts.
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void fail (), succ ();
void forkn (int), child (), parent (int);
static pid_t *pids;

int main (int argc, char *argv[])
{
    int n;
    if (argc == 1) fail();
    setbuf(stdout, NULL);
    n = atoi(argv[1]);
    pids = malloc(n * sizeof(pid_t));
    forkn(n);
    parent(n);
    return 0;
}

void forkn (int n)
{
    int pid;
    while (n-- > 0) switch (pid = fork()) {
        case -1: fail();
        case 0: child(); succ();
        default: pids[n] = pid;
    }
}

void child ()
{
    while (1) {
        sleep(4);
        printf("child %d is still alive\n", getpid());
    }
}

void parent (int n)
{
    int i;
    /* print children */
    printf("children: ");
    for (i = 0; i < n; i++) printf("%d ", pids[i]);
    puts("\n----");
    /* kill every n sec */
    for (i = 0; i < n; i++) {
        sleep(i ? 4 : 6);
        printf("killing %d\n", pids[i]);
        kill(pids[i], SIGKILL);
        printf("%d dead\n", wait(NULL));
    } 
    puts("parent exited");
}

void fail ()
{
    exit(EXIT_FAILURE);
}

void succ ()
{
    exit(EXIT_SUCCESS);
}
