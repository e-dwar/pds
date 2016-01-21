#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/mman.h>

typedef struct {
    sem_t semp;
} shared_t;

void
parent (shared_t *shared, int *fds)
{
    char buf[] = "_";
    printf("parent  : entering\n");
    close(fds[1]);
    while (read(fds[0], buf, 1) > 0) {
        printf("parent  : sem wait\n");
        assert(sem_wait(&(shared->semp)) != -1);
        printf("parent  : reading '%s'\n", buf);
    }
    close(fds[0]);
    printf("parent  : exiting\n");
}

void
child1 (shared_t *shared, int *fds)
{
    int i = 3;
    char buf[] = "_";
    char s[] = "cba";
    printf("child 1 : entering\n");
    close(fds[0]);
    while (i-- > 0) {
        buf[0] = s[i];
        write(fds[1], buf, 1);
        printf("child 1 : writing '%s'\n", buf);
        printf("child 1 : sem post\n");
        assert(sem_post(&(shared->semp)) != -1);
    }
    close(fds[1]);
    printf("child 1 : exiting\n");
}

void
child2 (shared_t *shared, int *fds)
{
    int i = 3;
    printf("child 2 : entering\n");
    close(fds[0]);
    while (i > 0) {
        sleep(1);
        printf("child 2 : waiting %ds\n", i--);
    }
    close(fds[1]);
    printf("child 2 : exiting\n");
}

int
main (int argc, char *argv[])
{
    shared_t *shared;
    int fds[2], size, prot, flags;
    sem_t semp;
    sem_init(&semp, 1, 0);
    assert(pipe(fds) == 0);
    size = sizeof(struct shared *);
    prot = PROT_READ | PROT_WRITE;
    flags = MAP_SHARED | MAP_ANONYMOUS;
    shared = (shared_t *)mmap(NULL, size, prot, flags, -1, 0);
    shared->semp = semp;

    switch (fork()) {
        case -1: exit(EXIT_FAILURE);
        case 0: child1(shared, fds); exit(EXIT_SUCCESS);
    }
    switch (fork()) {
        case -1: exit(EXIT_FAILURE);
        case 0: child2(shared, fds); exit(EXIT_SUCCESS);
    }
    parent(shared, fds);
    return 0;
}




























