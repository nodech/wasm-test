#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int from_arg_1(struct args_s *args) {
  return args->arg1 + args->arg2;
}

char *from_arg_2(struct args_s *args) {
  return args->arg3;
}

int from_arg_st1(struct args_s args) {
  return args.arg1 + args.arg2;
}

char *from_arg_st2(struct args_s args) {
  return args.arg3;
}

struct args_s something_with_stack(struct args_s *args) {
  unsigned char buffer[10];
  /* char *buffer2 = malloc(10); */

  for (int i = 0; i < 10; i++) {
    buffer[i] = i;
    /* buffer2[i] = 'a' + i; */
  }

  /* buffer[0] |= args->arg1 & 0xff; */
  /* buffer[1] |= args->arg2 & 0xff; */
  /* buffer2[0] |= args->arg1 & 0xff; */
  /* buffer2[1] |= args->arg2 & 0xff; */

  struct args_s result = {
    .arg1 = buffer[0],
    .arg2 = 111,
    .arg3 = NULL
  };

  return result;
}
