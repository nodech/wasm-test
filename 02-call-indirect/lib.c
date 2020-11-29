#include "lib.h"

int plus1(int number) {
  return number + 1;
}

void n_times(int fn(int number), int n) {
  for (int i = 0; i < n; i++) {
    fn(n);
  }
}
