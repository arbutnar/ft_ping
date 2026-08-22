#include "ft_ping.h"

t_flags g_flags = { 0 };

int process_arguments(int argc, char *argv[], char ***hosts) {
    int     opt, idx, nmemb;

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
                if (optopt == '?')
                    return print_help();
                return print_hint();
            default:
                if (g_flags.help == 1)
                    return print_help();
                break;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "ft_ping: missing host operand\n");
        return print_hint();
    }

    nmemb =  argc - optind;
    *hosts = calloc(nmemb, sizeof(char *));
    for (int i = 0; i < nmemb; i++) {
        (*hosts)[i] = argv[optind++];
        printf("%s\n", (*hosts)[i]);
    }

    return 0;
}

// int ft_ping(char *host) {

// }

int main(int argc, char *argv[]) {
    int     exit_status = 0;
    char    **hosts __attribute__((cleanup(free_hosts))) = NULL;

    exit_status = process_arguments(argc, argv, &hosts);
    if (hosts == NULL)
        return exit_status;
    // for (int i = 0; hosts[i] != NULL && exit_status != 1; i++) {
    //     exit_status = ft_ping(hosts[i]);
    // }

    return exit_status;
}
