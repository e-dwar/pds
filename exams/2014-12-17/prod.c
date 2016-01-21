#include <string.h>
#include <assert.h>
#include "commons.h"

int
genere (message_t *msg)
{
    static int n = 3;
    strcpy(&(msg->text), "allo");
    return (n--) == 0 ? -1 : 0;
}

void
producteur (int fd)
{
    message_t msg;
    while (genere(&msg) == 0) {
        assert(write(fd, msg.text, TEXTSIZE) != -1);
    }
}

int
main (int argc, char *argv[])
{
    int fd;
    fd = open("pipe", O_WRONLY);
    if (fd == -1) return -1;
    producteur(fd);
    if (close(fd) == -1) return -1;
    return 0;
}
