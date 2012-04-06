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
    qt = require('..'),
    test = require('./test');
    
var app = new qt.QApplication();

// Constructor
{
  var path = new qt.QPainterPath;
  assert.ok(path);
  assert.equal(path.currentPosition().x(), 0);
  assert.equal(path.currentPosition().y(), 0);
}

// moveTo
{
  var path = new qt.QPainterPath;
  path.moveTo(new qt.QPointF(123, 456));
  var point = path.currentPosition();
  assert.equal(point.x(), 123);
  assert.equal(point.y(), 456);
}

// lineTo
{
  var path = new qt.QPainterPath;
  path.lineTo(new qt.QPointF(1, 2));
  var point = path.currentPosition();
  assert.equal(point.x(), 1);
  assert.equal(point.y(), 2);
}

// closeSubpath
{
  var path = new qt.QPainterPath;
  path.lineTo(new qt.QPointF(1, 2));
  var point = path.currentPosition();
  assert.equal(point.x(), 1);
  assert.equal(point.y(), 2);

  path.closeSubpath();
  var point2 = path.currentPosition();
  assert.equal(point2.x(), 0);
  assert.equal(point2.y(), 0);  
}
