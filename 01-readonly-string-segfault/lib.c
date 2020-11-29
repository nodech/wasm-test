#include <string.h>
#include "lib.h"

void replace_dots(char *str) {
  int len = strlen(str);
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '.')
      str[i] = '!';
  }
}
