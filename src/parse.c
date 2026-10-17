#include "ft_ping.h"

static struct argp_option options[] = {
    // name, key, arg, flags, doc, group
    {NULL, 0, NULL, 0, "Options valid for all request types:\n", 1},
    {"verbose", 'v', NULL, 0, "verbose output", 0},
    {"count", 'c', "NUMBER", 0, "stop after sending NUMBER packets", 0},
    {NULL, 0, NULL, 0, "Options valid for --echo requests:\n", 2},
    {"size", 's', "NUMBER", 0, "send NUMBER data octets", 0},
    {0}};

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
  t_ping* ping = state->input;

  switch (key) {
    case 'v':
      ping->verbose = true;
      break;
    case 'c':
      ping->count = atoi(arg);
      break;
    case 's':
      ping->size = atoi(arg);
      break;
    case ARGP_KEY_ARGS:  // all remaining non-option arguments
      ping->hosts = state->argv + state->next;
      ping->nhosts = state->argc - state->next;
      break;
    case ARGP_KEY_NO_ARGS:                        // no host given
      argp_error(state, "missing host operand");  // prints hint, exits 64
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = "HOST ...",
    .doc = "Send ICMP ECHO_REQUEST packets to network hosts.",
};

void parse_args(int argc, char* argv[], t_ping* ping) {
  argp_parse(&argp, argc, argv, 0, NULL, ping);
}
