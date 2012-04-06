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

var qt = require('..');

var app = new qt.QApplication();

var window = new qt.QWidget;
var area = new qt.QScrollArea(window);
var widget = new qt.QWidget(area);
area.setWidget(widget);
area.setFrameShape(0); // no frame

window.resize(640, 480);
area.resize(640, 480);
widget.resize(1000, 1000);

window.show();
area.show();
widget.show();

var pixmap = new qt.QPixmap(1000, 1000);

widget.paintEvent(function(){
  console.log('paint!');
  var p = new qt.QPainter();
  p.begin(widget);
  p.drawPixmap(0, 0, pixmap);
  p.end();
});

var painter = new qt.QPainter();
painter.begin(pixmap);
painter.fillRect(0, 0, 1000, 1000, 3);

widget.mousePressEvent(function(e) {
  console.log('clicked:', e.x(), e.y());
  painter.fillRect(e.x(), e.y(), 10, 10, 9);
  widget.update();
});

widget.mouseMoveEvent(function(e) {
  console.log('moved:', e.x(), e.y());
  painter.fillRect(e.x(), e.y(), 10, 10, 9);
  widget.update();
});

// Prevent objects from being GC'd
global.window = window;
global.area = area;
global.widget = widget;

setInterval(function() {
  app.processEvents();
}, 0);
