#ifndef FT_PING_H
#define FT_PING_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include <errno.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

typedef struct {
  int verbose;
  int help;
} t_flags;

// print.c
int print_hint();
int print_help();

// utils.c
void free_hosts(char*** hosts);

// icmp.c
int init_icmp_socket(void);
int send_echo_request(int sockfd, struct sockaddr_in* dest, uint16_t seq);

#endif /* FT_PING_H ****/