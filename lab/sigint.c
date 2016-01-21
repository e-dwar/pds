#include <stdio.h>
#include <signal.h>

static int n = 3;

void f (int sig) 
{
    printf("\nsignal received: %d\n", sig);
    if (--n == 0) kill(getpid(), SIGKILL);
}

int
main (int argc, char *argv[])
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = &f;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    while (1) {
        printf("sigint remaining: %d\n", n);
        pause();
        printf("resumed\n");
    }
    return 0;
}
