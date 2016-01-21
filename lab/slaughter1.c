/**
 * Les processus fils se terminent à partir de 3 secondes.
 * Le processus père ne s'arrête pas de lui-même et affiche
 * un message dès qu'il reçoit les signaux SIGCHLD et SIGCONT.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <string.h>

#define N 3
void handler (int);
void fail (), succ (), child (int), parent (), aboutme ();
void on (int, void (*handler) (int));
static pid_t pids[N];

int main () 
{
    int i;
    pid_t pid;
    setbuf(stdout, NULL);
    pids[N - 1] = 0;
    for (i = 0; i < N - 1; i++) {
        switch (pid = fork()) {
            case -1: fail();
            case 0: child(i); succ();
            default: pids[i] = pid;
        }
    }
    parent();
    return 0;
}

void child (int i)
{
    sleep(3 + i);
}

void parent ()
{
    int status;
    aboutme();
    on(SIGCHLD, &handler);
    on(SIGCONT, &handler);
    while (1) {
        sleep(10);
        puts("i am still alive");
    }
}

void on (int sig, void (*handler) (int))
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(sig, &sa, NULL) == 0);
}

void handler (int sig)
{
    int pid = getpid();
    char *signame = strsignal(sig);
    printf("parent (%d) received \"%s\" (%d)", pid, signame, sig);
    if (sig == SIGCHLD) printf(", child: %d", waitpid(-1, NULL, WNOHANG));
    putchar('\n');
}

void aboutme ()
{
    int i = 0;
    printf("me: %d\nand my children: ", getpid());
    while (pids[i]) printf("%d ", pids[i++]);
    puts("\n----");
}

void fail () 
{
    exit(EXIT_FAILURE);
}

void succ ()
{
    exit(EXIT_SUCCESS);
}
