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
    fs = require('fs'),
    path = require('path'),
    qt = require('..'),
    test = require('./test');
    
var app = new qt.QApplication();

// Constants
var width = 100, height = 100;

// Painter initialization: Widget
// For widgets it must begin() inside paintEvent()
{
  var widget = new qt.QWidget();
  var paintEventCalled = false;
  widget.paintEvent(function() {
    var painter = new qt.QPainter();
    assert.equal( painter.begin(widget), true );
    assert.equal( painter.end(), true );
    paintEventCalled = true;
  });
  widget.show();
  app.processEvents();
  assert.equal( paintEventCalled, true );
}

// Painter initialization: Pixmap (begin)
{
  var pixmap = new qt.QPixmap(width, height);
  var painter = new qt.QPainter();
  assert.equal( painter.isActive(), false );
  assert.equal( painter.begin(pixmap), true );
  assert.equal( painter.isActive(), true );
  assert.equal( painter.end(), true );
}

// drawPixmap() - crash test only
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var pixmap2 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  painter.drawPixmap(0, 0, pixmap2);

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// drawPixmap() - wrong arg
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter();
  painter.begin(pixmap1);
  var flag = false;
  try {
    painter.drawPixmap(0, 0);
  } catch (e) {
    flag = true;
  }
  assert.ok(flag, 'drawPixmap should throw error with bad args');

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// strokePath() - crash test
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  var path = new qt.QPainterPath;
  var pen = new qt.QPen;
  painter.strokePath(path, pen);

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// strokePath() - wrong args
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  var flag = false;
  try {
    painter.strokePath(1, '2');
  } catch (e) {
    flag = true;
  }
  assert.ok(flag, 'strokePath should throw error with bad args');

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setPen() - crash test only
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  painter.setPen(new qt.QPen);

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setPen() - wrong args
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  var flag = false;
  try {
    painter.setPen(1);
  } catch (e) {
    flag = true;
  }
  assert.ok(flag, 'setPen should throw error with bad args');

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setFont() - crash test
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  painter.setFont(new qt.QFont);

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setFont() - wrong args
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  var flag = false;
  try {
    painter.setFont(1);
  } catch (e) {
    flag = true;
  }
  assert.ok(flag, 'setPen should throw error with bad args');

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setMatrix() - crash test only
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  painter.setMatrix(new qt.QMatrix);

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

// setMatrix() - wrong args
{
  var pixmap1 = new qt.QPixmap(100, 100);
  var painter = new qt.QPainter;
  painter.begin(pixmap1);

  var flag = false;
  try {
    painter.setMatrix(1);
  } catch (e) {
    flag = true;
  }
  assert.ok(flag, 'setMatrix should throw error with bad args');

  painter.end(); // calling .end() before leaving scope ensures pixmaps won't 
                 // get GC'd before painter is done (segfault!)
}

//
// Regression tests
//

{
  var pixmap = new qt.QPixmap(width, height);
  var painter = new qt.QPainter();

  painter.begin(pixmap);

  // save()-restore()

  test.regression('painter-drawtext-saved-black', pixmap, function() {
    painter.save();
    pixmap.fill();
    var brush = new qt.QBrush(qt.GlobalColor.green);
    var pen = new qt.QPen(brush, 2);
    painter.setPen(pen);
    
    painter.restore();
    painter.drawText(0, 20, "saved");
  });

  // fillRect()

  test.regression('painter-fillrect-blue-sq', pixmap, function() {
    pixmap.fill();
    painter.fillRect(0, 0, 10, 10, qt.GlobalColor.blue);
  });

  test.regression('painter-fillrect-red-sq', pixmap, function() {
    pixmap.fill();
    painter.fillRect(0, 0, 10, 10, new qt.QBrush(qt.GlobalColor.red));
  });

  test.regression('painter-fillrect-green-sq', pixmap, function() {
    pixmap.fill();
    painter.fillRect(0, 0, 10, 10, new qt.QColor(0, 255, 0));
  });

  test.regression('painter-fillrect-transp-boxes', pixmap, function() {
    pixmap.fill();
    painter.fillRect(0, 0, 30, 30, new qt.QColor(0, 255, 0));
    painter.fillRect(15, 15, 45, 45, new qt.QColor(0, 0, 255, 125));
  });

  // drawText()

  test.regression('painter-drawtext-hello-black', pixmap, function() {
    pixmap.fill();
    painter.drawText(0, 20, "hello");
  });

  test.regression('painter-drawtext-hello-green', pixmap, function() {
    pixmap.fill();
    var brush = new qt.QBrush(qt.GlobalColor.green);
    var pen = new qt.QPen(brush, 2);
    painter.setPen(pen);
    painter.drawText(0, 20, "hello");
  });

  // drawImage()

  test.regression('painter-drawimage', pixmap, function() {
    var image = new qt.QImage('resources/qimage.png');
    pixmap.fill();
    painter.drawImage(20, 20, image);
  });

  painter.end();
}
