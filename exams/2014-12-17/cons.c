#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include "commons.h"

int
utilise (message_t *msg)
{
    static int n = 3;
    printf("msg: %s\n", msg->text);
    return (n--) == 0 ? -1 : 0;
}

void
consommateur (int fd)
{
    message_t msg;
    int n, stop_using = 0;
    while (stop_using == 0) {
        n = read(fd, msg.text, TEXTSIZE - 1);
        assert(n != -1);
        msg.text[n] = '\0';
        if (n == 0) stop_using = 1;
        else stop_using = utilise(&msg);
    }
}

int
main (int argc, char *argv[])
{
    int fd;
    fd = open("pipe", O_RDONLY);
    if (fd == -1) return -1;
    consommateur(fd);
    if (close(fd) == -1) return -1;
    return 0;
}
