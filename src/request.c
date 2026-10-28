#include "ft_ping.h"

void print_ping_header(char* host, t_ping ping) {
  printf("PING %s (%s): %ld data bytes\n", host, ping.dest_ip,
         ping.flags.payload_size);
}

uint16_t build_checksum(void* packet, size_t packet_len) {
  uint8_t* buf = packet;
  uint32_t sum = 0;
  uint16_t word;

  for (; packet_len > 1; packet_len -= 2, buf += 2) {
    memcpy(&word, buf, sizeof(word));
    sum += word;
  }
  if (packet_len == 1)
    sum += *buf;

  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return (uint16_t)~sum;
}

void build_echo_request(t_ping* ping, t_icmpkt* icmpkt) {
  icmpkt->header.code = 0;  // boh perchè?
  icmpkt->header.type = ICMP_ECHO;
  icmpkt->header.un.echo.id = htons((uint16_t)getpid());
  icmpkt->header.un.echo.sequence = htons((uint16_t)ping->request_count);

  size_t i = 0;
  struct timeval send_time;

  gettimeofday(&send_time, NULL);
  if (ping->flags.payload_size >= sizeof(struct timeval)) {
    i = sizeof(struct timeval);
    memcpy(icmpkt->payload, &send_time, sizeof(struct timeval));
  }
  for (; i < ping->flags.payload_size; i++)
    icmpkt->payload[i] = (char)i;

  icmpkt->packet_len = sizeof(icmpkt->header) + ping->flags.payload_size;
  icmpkt->header.checksum = 0;
  icmpkt->header.checksum = build_checksum(icmpkt, icmpkt->packet_len);
}

void send_echo_request(t_ping* ping, t_icmpkt* icmpkt) {
  build_echo_request(ping, icmpkt);

  if (sendto(ping->sockfd, icmpkt, icmpkt->packet_len, 0,
             (struct sockaddr*)&ping->dest_addr, sizeof(ping->dest_addr)) < 0) {
    perror("ping: sending packet");
    exit(EXIT_FAILURE);
  }
  ping->request_count++;
}