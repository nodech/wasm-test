const http = require('http');
const path = require('path');
const url = require('url');
const fs = require('fs');
const pfs = fs.promises;

const mimes = {
  '.wasm': 'application/wasm',
  '.html': 'text/html',
  '.js': 'text/javascript'
};

http.createServer(function (req, res) {
  const q = url.parse(req.url, true);
  let {pathname} = q;

  if (pathname === '/')
    pathname = 'index.html';

  let fileName = path.join('.', pathname);

  fs.exists(fileName, async (exists) => {
    if (!exists) {
      console.error('File %s not found', fileName);
      res.end();
      return false;
    }

    const ext = path.extname(fileName);

    if (!mimes[ext]) {
      console.error('Ext not supported: ', ext);
      res.end();
      return ''
    }
    console.log('Receiving: %s, Mime: %s', fileName, mimes[ext]);
    res.setHeader('Content-Type', mimes[ext]);
    res.write(await pfs.readFile(fileName));
    res.end();
  });
}).listen(8180);
