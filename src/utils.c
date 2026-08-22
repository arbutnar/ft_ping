#include "ft_ping.h"

void    free_hosts(char ***hosts) {
    if (*hosts != NULL)
        free(*hosts);
}