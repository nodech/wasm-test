
(async () => {
  const memory = new WebAssembly.Memory({
    initial: 1,
  });

  const table = new WebAssembly.Table({
    initial: 1,
    element: 'anyfunc'
  });

  const { instance, module } = await WebAssembly.instantiateStreaming(
    await fetch('./main.wasm'),
    {
      wasi_snapshot_preview1: {
        fd_write: (...args) => {
          console.log(args);
          return 0;
        },
        proc_exit: (status) => {
          console.log('Proc exit: ', status);
          return 0;
        }
      },
      env: {

      }
      //memory,
      //table
    }
  );

  const buffer = memory.buffer;
  const HEAP8 = new Uint8Array(buffer);

  //const param0 = "test...";
  console.log(module);
  console.log(instance);
  console.log(instance.exports);
  //console.log("MemAddr:", instance.exports.get_magic_str());

  window.instance = instance;
  window.module = module;
  window.HEAP8 = HEAP8;
  //console.log(instance.exports.replace_dots(param0));
  //console.log(buffer);
})().then(() => {
  console.log('done');
}).catch((e) => {
  console.error(e);
});
