#include "ft_ping.h"

void resolve_target(char* host, t_ping* ping) {
  struct addrinfo hints = {0};
  struct addrinfo* res;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_RAW;
  hints.ai_protocol = IPPROTO_ICMP;
  hints.ai_flags = 0;
  if (getaddrinfo(host, NULL, &hints, &res) != 0) {
    fprintf(stderr, "ft_ping: unknown host\n");
    exit(EXIT_FAILURE);
  }
  // cast the pointer to the IPv4-specific layout
  ping->dest_addr = *(struct sockaddr_in*)res->ai_addr;
  inet_ntop(AF_INET, &ping->dest_addr.sin_addr, ping->dest_ip,
            sizeof(ping->dest_ip));
  freeaddrinfo(res);
}

int main(int argc, char** argv) {
  t_flags flags = {.payload_size = PING_DEFAULT_PAYLOAD_SIZE};
  t_ping ping = {.flags = flags};
  t_icmpkt request_icmpkt = {0};

  parse_args(argc, argv, &ping);
  ping.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (ping.sockfd == -1) {
    if (errno == EPERM || errno == EACCES)
      fprintf(stderr, "ft_ping: Lacking privilege for icmp socket.\n");
    else
      perror("ft_ping: socket");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < ping.nhosts; i++) {
    resolve_target(ping.hosts[i], &ping);
    print_ping_header(ping.hosts[i], ping);
    send_echo_request(&ping, &request_icmpkt);
    while (1) {
      int readyfds;
      fd_set readfds;
      struct timeval timeout;

      FD_ZERO(&readfds);
      FD_SET(ping.sockfd, &readfds);
      timeout.tv_sec = 1;

      readyfds = select(ping.sockfd + 1, &readfds, NULL, NULL, &timeout);
      if (readyfds == -1) {
        perror("ft_ping: select");
        exit(EXIT_FAILURE);
      } else if (readyfds == 0)
        send_echo_request(&ping, &request_icmpkt);
      else
        receive_echo_reply(&ping);
    }
  }

  return 0;
}
