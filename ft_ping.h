#ifndef     FT_PING_H
# define    FT_PING_H

# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
#include <getopt.h>

typedef struct {
    int verbose;
    int help;
} t_flags;


// print.c
int print_hint();
int print_help();

// utils.c
void    free_hosts(char ***hosts);

#endif /* FT_PING_H */