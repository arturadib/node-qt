#!/usr/bin/env node
try {
  require('shelljs/make');
} catch(e) {
  console.log('Could not load ShellJS. Did you forget to `npm install`?\n');
  process.exit(1);
}

var root = __dirname;

target.test = function() {
  cd(root);
  
  echo('_________________________________________________________________');
  echo('Running Node-Qt tests');
  echo();
  
  cd('test');
  rm('-f', 'img-test/*');
  ls('q*.js').forEach(function(f) {
    echo('Running test file '+f);
    exec('node '+f);
  });
}

target.ref = function() {
  cd(root);

  cd('test');
  echo('_________________________________________________________________');
  echo('Node-Qt tests: Overwriting reference images');
  rm('-f', 'img-ref/*');
  mv('img-test/*', 'img-ref');
}
