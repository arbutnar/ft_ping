#include "ft_ping.h"

int main(int argc, char** argv) {
  t_ping ping = {0};

  parse_args(argc, argv, &ping);
  // printf("count: %u\nsize: %u\nverbose: %d\nnhosts: %u\n", ping.count,
  //        ping.size, ping.verbose, ping.nhosts);
  // for (unsigned i = 0; i < ping.nhosts; i++)
  //   printf("host[%u]: %s\n", i, ping.hosts[i]);
  return 0;
}
