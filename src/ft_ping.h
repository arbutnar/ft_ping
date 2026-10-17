#ifndef FT_PING_H
#define FT_PING_H

#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <unistd.h>

#include <errno.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

typedef struct {
  unsigned nhosts;
  char** hosts;

  unsigned count;
  unsigned size;
  bool verbose;
} t_ping;

// parse.c
void parse_args(int argc, char* argv[], t_ping* ping);

#endif /* FT_PING_H */