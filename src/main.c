#include "ft_ping.h"

t_flags g_flags = { 0 };

char    **process_arguments(int argc, char *argv[], int *exitcode) {
    int     opt, idx, nmemb;
    char    **hosts;

    struct option long_opts[] = {
        {"verbose", no_argument,    NULL, 'v'},
        {"help",    no_argument,    &g_flags.help, 1},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "v", long_opts, &idx)) != -1) {
        switch (opt) {
            case 'v':
                g_flags.verbose = 1;
                break;
            case '?':
                if (optopt == '?') {
                    *exitcode = print_help();
                    return NULL;
                }
                *exitcode = print_hint();
                return NULL;
            default:
                if (g_flags.help == 1) {
                    *exitcode = print_help();
                    return NULL;
                }
                break;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "ft_ping: missing host operand\n");
        *exitcode = print_hint();
        return NULL;
    }

    nmemb =  argc - optind;
    hosts = calloc(nmemb, sizeof(char *));
    for (int i = 0; i < nmemb; i++) {
        hosts[i] = argv[optind++];
        printf("%s\n", hosts[i]);
    }

    return hosts;
}

// int ft_ping(t_flags flags) {

// }

int main(int argc, char *argv[]) {
    int     exitcode = 0;
    char    **hosts __attribute__((cleanup(free_hosts)));

    hosts = process_arguments(argc, argv, &exitcode);
    if (hosts == NULL)
        return exitcode;
    return 0;
}
