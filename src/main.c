#include "ft_ping.h"

void resolve_target(char* host, t_ping* ping) {
  struct addrinfo hints = {0};
  struct addrinfo* res;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_RAW;
  hints.ai_protocol = IPPROTO_ICMP;
  hints.ai_flags = 0;
  if (getaddrinfo(host, NULL, &hints, &res) != 0) {
    printf("ft_ping: unknown host\n");
    exit(EXIT_FAILURE);
  }

  // cast the pointer to the IPv4-specific layout
  ping->dest_addr = *(struct sockaddr_in*)res->ai_addr;
  inet_ntop(AF_INET, &ping->dest_addr.sin_addr, ping->dest_ip,
            sizeof(ping->dest_ip));
  freeaddrinfo(res);

  printf("%s\n", ping->dest_ip);
}

int main(int argc, char** argv) {
  t_ping ping = {0};

  parse_args(argc, argv, &ping);
  // printf("count: %u\nsize: %u\nverbose: %d\nnhosts: %u\n", ping.count,
  //        ping.size, ping.verbose, ping.nhosts);
  // for (unsigned i = 0; i < ping.nhosts; i++)
  //   printf("host[%u]: %s\n", i, ping.hosts[i]);

  // int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  for (unsigned i = 0; i < ping.nhosts; i++) {
    resolve_target(ping.hosts[i], &ping);
  }

  return 0;
}
