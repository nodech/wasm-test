WebAssembly tests
=================

Experimenting with webassembly and C.

This will have list of directories with specific structure:
  - C lang tests - directory includes:
    - lib.c - this will be built as `STANDALONE WASM` library that exports
    functions.
    - main.c - to build native binary with GCC or Clang.
    - TODO:...
