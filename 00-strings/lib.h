#include <wasm_helpers.h>

EXPORT static const char magic_str[] = "00-string";
EXPORT const char *get_magic_str();
EXPORT void replace_dots(char *str);
EXPORT int get_len(const char *str);
