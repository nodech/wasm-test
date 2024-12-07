#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main() {
  struct args_s args = {1, 2, "hello"};
  struct args_s args2 = {3, 4, "world"};
  struct args_s *args3 = malloc(sizeof(struct args_s));
  args3->arg1 = 5;
  args3->arg2 = 6;
  args3->arg3 = "foo";

  printf("from_arg_1: %d\n", from_arg_1(&args));
  printf("from_arg_2: %s\n", from_arg_2(&args));

  printf("from_arg_st1: %d\n", from_arg_st1(args2));
  printf("from_arg_st2: %s\n", from_arg_st2(args2));

  // Do malloced stuff
  printf("from_arg_1: %d\n", from_arg_1(args3));
  printf("from_arg_2: %s\n", from_arg_2(args3));
  printf("from_arg_st1: %d\n", from_arg_st1(*args3));
  printf("from_arg_st2: %s\n", from_arg_st2(*args3));

  // print addrs.
  printf("args: %p, args2: %p, args3: %p\n", &args, &args2, args3);
  printf("args: %p, args2: %p, args3: %p\n", args.arg3, args2.arg3, args3->arg3);

  struct args_s result = something_with_stack(&args);

  printf("something_with_stack: %d %d %s\n",
         result.arg1, result.arg2, result.arg3);

  printf("something_with_stack: %p, str: %p\n",
         &result, result.arg3);

  free(args3);
}
