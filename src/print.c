#include "ft_ping.h"

int print_hint() {
    dprintf(STDERR_FILENO, "Try 'ft_ping --help' for more information.\n");
    return 64;
}

int print_help() {
    dprintf(STDERR_FILENO, "Usage: ft_ping [OPTION...] HOST ...\n");
    dprintf(STDERR_FILENO, "Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
    dprintf(STDERR_FILENO, "Options valid for all request types::\n\n");
    dprintf(STDERR_FILENO, "-v, --verbose              verbose output\n\n");
    dprintf(STDERR_FILENO, "Options valid for --echo requests:\n\n");
    dprintf(STDERR_FILENO, "-?, --help                 give this help list\n\n");
    dprintf(STDERR_FILENO, "Mandatory or optional arguments to long options are also mandatory or optional\n");
    dprintf(STDERR_FILENO, "for any corresponding short options.\n\n");
    dprintf(STDERR_FILENO, "Options marked with (root only) are available only to superuser.\n");
    return 0;
}
