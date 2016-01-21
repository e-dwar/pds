#include <stdio.h>
#include <getopt.h>

int main (int argc, char *argv[])
{
    int opti;
    struct option rules[] = {
        { "allo", required_argument, 0, 0 },
        { "alluil", no_argument, 0, 0 }
    };
    while (getopt_long(argc, argv, "", rules, &opti) != -1) {
        printf("%s '%s'\n", rules[opti].name, optarg);
    }
    printf("optind = %d\n", optind);
    return 0;
}
