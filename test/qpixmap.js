// Copyright (c) 2012, Artur Adib
// All rights reserved.
//
// Author(s): Artur Adib <aadib@mozilla.com>
//
// You may use this file under the terms of the New BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Artur Adib nor the
//       names of contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL ARTUR ADIB BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

var assert = require('assert'),
    fs = require('fs');
    path = require('path');
    qt = require('..'),
    test = require('./test');

var app = new qt.QApplication();

// Constructor
{
  var pixmap = new qt.QPixmap(50, 60);
  assert.equal(pixmap.width(), 50);
  assert.equal(pixmap.height(), 60);
}

// save()
{
  var pixmap = new qt.QPixmap(10, 10);
  if (fs.existsSync('./__pixmap.png'))
    fs.unlinkSync('__pixmap.png');
  pixmap.save('__pixmap.png');
  assert.equal(fs.existsSync('./__pixmap.png'), true, '.save() works');
  fs.unlinkSync('./__pixmap.png');
}

// Bitmap regressions
{
  var pixmap = new qt.QPixmap(100, 100);

  // can't test regression on a null pixmap since it contains garbage

  test.regression('pixmap-fill-default', pixmap, function() {
    pixmap.fill();
  });

  test.regression('pixmap-fill-red', pixmap, function() {
    pixmap.fill(new qt.QColor(255, 0, 0));
  });
}
