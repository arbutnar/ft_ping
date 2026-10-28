#ifndef FT_PING_H
#define FT_PING_H

#include <argp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sysexits.h>
#include <unistd.h>

#define MAX_IPHDR_SIZE 60
#define PING_DEFAULT_PAYLOAD_SIZE 56
#define PING_MAX_PAYLOAD_SIZE \
  UINT16_MAX - MAX_IPHDR_SIZE - (MAX_IPHDR_SIZE + 8 + 8)
// 65535 - 60 (max IP hdr) - 76 (max ICMP error: 8 + 60 inner IP hdr + 8)

typedef struct {
  struct icmphdr header;
  char payload[PING_MAX_PAYLOAD_SIZE];
  size_t payload_len;
  size_t packet_len;
  uint16_t sequence;
} t_icmpkt;

typedef struct {
  size_t count;
  size_t payload_size;
  bool verbose;
} t_flags;

typedef struct {
  int sockfd;
  int nhosts;
  char** hosts;
  struct sockaddr_in dest_addr;
  char dest_ip[INET_ADDRSTRLEN];
  unsigned long request_count;
  t_flags flags;
} t_ping;

// parse.c
void parse_args(int argc, char* argv[], t_ping* ping);

// request.c
void print_ping_header(char* host, t_ping ping);
void send_echo_request(t_ping* ping, t_icmpkt* icmpkt);

// reply.c
int receive_echo_reply(t_ping* ping);

#endif /* FT_PING_H */