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
  var area = new qt.QScrollArea();
  area.setObjectName('top1');
  assert.equal(area.objectName(), 'top1');

  area.resize(800, 600);
  assert.equal(area.size().width(), 800);
  assert.equal(area.size().height(), 600);
  assert.equal(area.width(), 800);
  assert.equal(area.height(), 600);

  area.resize(200, 300);
  assert.equal(area.size().width(), 200);
  assert.equal(area.size().height(), 300);
  assert.equal(area.width(), 200);
  assert.equal(area.height(), 300);
}

{
  var area = new qt.QScrollArea();

  // Sanity check to make prototype/private properties are not leaking
  area.setObjectName('top2');
  assert.equal(area.objectName(), 'top2');
  area.resize(100, 200);
  assert.equal(area.size().width(), 100);
  assert.equal(area.size().height(), 200);
}

// Constructor- parent widget
{
  var widget = new qt.QWidget;
  widget.setObjectName('topwidget');

  var area = new qt.QScrollArea(widget);
  assert.equal(area.parent(), 'topwidget');
  assert.equal(area.x(), 0);
  assert.equal(area.y(), 0);

  area.move(12, 34);
  assert.equal(area.x(), 12);
  assert.equal(area.y(), 34);
}

// setWidget()
{
  var area = new qt.QScrollArea(),
      widget = new qt.QWidget();

  assert.equal(area.widget(), 0);
  area.setWidget(widget);
  assert.equal(area.widget(), 1);
}

// scrollBars
{
  var area = new qt.QScrollArea();
  assert.equal(area.horizontalScrollBar() instanceof qt.QScrollBar, true);
  assert.equal(area.verticalScrollBar() instanceof qt.QScrollBar, true);
}
