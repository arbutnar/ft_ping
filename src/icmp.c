#include "ft_ping.h"

#define PACKET_SIZE 64

int init_icmp_socket(void) {
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1) {
        fprintf(stderr, "ft_ping: socket: %s\n", strerror(errno));
        return -1;
    }
    return sockfd;
}

static uint16_t checksum(void *data, size_t len) {
    uint32_t    sum;
    uint16_t    *buf;

    sum = 0;
    buf = data;
    while (len > 1) {
        sum += *buf++;
        len -= 2;
    }
    if (len == 1)
        sum += *(uint8_t *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ~sum;
}

int send_echo_request(int sockfd, struct sockaddr_in *dest, uint16_t seq) {
    char            packet[PACKET_SIZE];
    struct icmphdr  *icmp;

    memset(packet, 0, sizeof(packet));
    icmp = (struct icmphdr *)packet;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid() & 0xFFFF;
    icmp->un.echo.sequence = seq;
    icmp->checksum = checksum(packet, sizeof(packet));

    if (sendto(sockfd, packet, sizeof(packet), 0,
            (struct sockaddr *)dest, sizeof(*dest)) == -1) {
        fprintf(stderr, "ft_ping: sendto: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}
