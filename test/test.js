var fs = require('fs'),
    path = require('path');

var testDir = __dirname+'/img-test/',
    refDir = __dirname+'/img-ref/';

if (!path.existsSync(testDir)) {
  console.log('! regression warning: img-test/ dir does not exist. creating it...')
  fs.mkdirSync(testDir);
}

exports.regression = function(name, pixmap, callback) {
  callback();
      
  pixmap.save(testDir+name+'.png');

  // Can't compare if refs don't exist
  if (!path.existsSync(refDir+name+'.png')) {
    console.log('! regression warning: could not find reference file for test:', name)
    return;
  }
  
  var testBuf = fs.readFileSync(testDir+name+'.png');
  var refBuf = fs.readFileSync(refDir+name+'.png');
  if (testBuf.toString() !== refBuf.toString()) {
    console.log('!!! image regression in test:', name);
  }
}
