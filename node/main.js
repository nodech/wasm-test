'use strict';

const path = require('path');
const fs = require('fs');
const fsp = fs.promises;

const ROOT = path.join(__dirname, '..');
//const WASM_FILE = path.join(ROOT, './01-readonly-string-segfault/out/main.wasm');
const WASM_FILE = path.join(ROOT, './00-strings/out/main.wasm');


(async () => {
  if (!fs.existsSync(WASM_FILE))
    throw new Error(WASM_FILE + ' not found.');

  let buffer, HEAP8;

  const wasmFile = await fsp.readFile(WASM_FILE);
  const compiled = await WebAssembly.compile(wasmFile);
  const instance = await WebAssembly.instantiate(compiled, {
    wasi_snapshot_preview1: {
      fd_write: (fd, bufPtr, count, what) => {
        console.log(fd, bufPtr, count, what);
        console.log(HEAP8[bufPtr]);
        for (let i = bufPtr; i < bufPtr + count; i++) {
          console.log(HEAP8[i]);
        }
        return count;
      },
      proc_exit: (code) => {
        console.log('Exit:', code);
        return process.exit(code);
      }
    }
  });

  buffer = instance.exports.memory.buffer;
  HEAP8 = new Uint8Array(buffer);

  instance.exports._start();

})().then(() => {
  console.log('done');
}).catch((e) => {
  console.error(e);
});
