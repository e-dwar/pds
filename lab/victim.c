#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

void
onSigint (int sig)
{
    puts("\nvictim received SIGINT");
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
    on(SIGINT, onSigint);
    pause();
    return 0;
}
