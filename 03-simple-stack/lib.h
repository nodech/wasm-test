#include <wasm_helpers.h>

struct args_s {
  int arg1;
  int arg2;
  char *arg3;
};

EXPORT int from_arg_1(struct args_s *args);
EXPORT char *from_arg_2(struct args_s *args);
EXPORT int from_arg_st1(struct args_s args);
EXPORT char *from_arg_st2(struct args_s args);
EXPORT struct args_s something_with_stack(struct args_s *args);
