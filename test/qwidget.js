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

var assert = require('assert');
var qt = require('..');

var app = new qt.QApplication();

// Core API
{
  var widget = new qt.QWidget();
  widget.setObjectName('top1');
  assert.equal(widget.objectName(), 'top1');

  widget.resize(800, 600);
  assert.equal(widget.size().width(), 800);
  assert.equal(widget.size().height(), 600);
  assert.equal(widget.width(), 800);
  assert.equal(widget.height(), 600);

  widget.resize(200, 300);
  assert.equal(widget.size().width(), 200);
  assert.equal(widget.size().height(), 300);
  assert.equal(widget.width(), 200);
  assert.equal(widget.height(), 300);

  assert.equal(widget.hasMouseTracking(), false);
  widget.setMouseTracking(true);
  assert.equal(widget.hasMouseTracking(), true);
}

{
  var widget = new qt.QWidget();

  // Sanity check to make prototype/private properties are not leaking
  widget.setObjectName('top2');
  assert.equal(widget.objectName(), 'top2');
  widget.resize(100, 200);
  assert.equal(widget.size().width(), 100);
  assert.equal(widget.size().height(), 200);

  var widget2 = new qt.QWidget(widget);
  assert.equal(widget2.parent(), 'top2');

  assert.equal(widget2.x(), 0);
  assert.equal(widget2.y(), 0);

  widget.resize(55, 66);
  assert.equal(widget.size().width(), 55);
  assert.equal(widget.size().height(), 66);

  widget2.move(12, 34);
  assert.equal(widget2.x(), 12);
  assert.equal(widget2.y(), 34);
}

// Events
{
  var capturedEvents = [];
  var widget = new qt.QWidget;

  // Handlers
  widget.mousePressEvent(function(e) {
    capturedEvents.push(e);
  });

  widget.mouseReleaseEvent(function(e) {
    capturedEvents.push(e);
  });

  widget.keyPressEvent(function(e) {
    capturedEvents.push(e);
  });

  widget.paintEvent(function() {
    capturedEvents.push('paintEvent');
  });

  // Triggers paintEvent()
  widget.show(); // capturedEvents: 0
  app.processEvents();
  assert.equal(capturedEvents[0], 'paintEvent');

  // Test mouse, keyboard, etc
  capturedEvents = [];
  var events = new qt.QTestEventList();
  events.addMouseClick(qt.MouseButton.LeftButton); // capturedEvents: 1
  events.addMouseClick(qt.MouseButton.RightButton); // capturedEvents: 2
  events.addKeyPress('a'); // capturedEvents: 3
  events.addKeyPress(qt.Key.Key_Left); // capturedEvents: 4
  events.simulate(widget);

  app.processEvents();

  // Event assertions
  assert.equal(capturedEvents[0].button(), qt.MouseButton.LeftButton); // mousepress
  assert.equal(capturedEvents[1].button(), qt.MouseButton.LeftButton); // mouserelease
  assert.equal(capturedEvents[2].button(), qt.MouseButton.RightButton); // mousepress
  assert.equal(capturedEvents[3].button(), qt.MouseButton.RightButton); // mouserelease
  assert.equal(capturedEvents[4].text(), 'a'); // keypress
  assert.equal(capturedEvents[5].key(), qt.Key.Key_Left); // keypress
}
