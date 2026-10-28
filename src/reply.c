#include "ft_ping.h"

int read_echo_reply(char* buf,
                    size_t buf_len,
                    struct iphdr* iphdr,
                    t_icmpkt* icmpkt) {
  if (buf_len < sizeof(struct iphdr))
    return -1;

  size_t iphdr_len;

  memcpy(iphdr, buf, sizeof(struct iphdr));
  iphdr_len = iphdr->ihl * 4;
  if (buf_len < iphdr_len + sizeof(struct icmphdr))
    return -1;

  memcpy(&icmpkt->header, buf + iphdr_len, sizeof(icmpkt->header));
  icmpkt->payload_len = buf_len - iphdr_len - sizeof(struct icmphdr);
  if (icmpkt->payload_len > PING_MAX_PAYLOAD_SIZE)
    icmpkt->payload_len = PING_MAX_PAYLOAD_SIZE;
  memcpy(icmpkt->payload, buf + iphdr_len + sizeof(struct icmphdr),
         icmpkt->payload_len);
  icmpkt->packet_len = icmpkt->payload_len + sizeof(struct icmphdr);
  return 0;
}

void print_echo_reply(struct iphdr* iphdr, t_icmpkt* icmpkt) {
  char address[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &iphdr->saddr, address, sizeof(address));

  printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%f ms\n",
         icmpkt->packet_len, address, icmpkt->sequence, iphdr->ttl, 0.0);
}

int receive_echo_reply(t_ping* ping) {
  ssize_t n_bytes;
  char buf[MAX_IPHDR_SIZE + sizeof(struct icmphdr) + PING_MAX_PAYLOAD_SIZE];
  struct iphdr iphdr = {0};
  t_icmpkt icmpkt = {0};

  n_bytes = recv(ping->sockfd, buf, sizeof(buf), 0);
  if (n_bytes == -1)
    return -1;
  if (read_echo_reply(buf, (size_t)n_bytes, &iphdr, &icmpkt) == -1)
    return -1;
  print_echo_reply(&iphdr, &icmpkt);
  return 0;
}