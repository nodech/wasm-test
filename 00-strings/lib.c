#include <string.h>
#include "lib.h"

const char *get_magic_str() {
  return magic_str;
}

int get_len(const char *str) {
  return strlen(str);
}

void replace_dots(char *str) {
  int len = get_len(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '.')
      str[i] = '!';
  }
}
