#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

void
onSigint (int sig)
{
    puts("\nkiller received SIGINT");
}

int
on (int signum, void handler(int))
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    return sigaction(signum, &sa, NULL);
}

int
main (int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    on(SIGINT, onSigint);
    pause();
    assert(kill(pid, SIGINT) == 0);
    return 0;
}
