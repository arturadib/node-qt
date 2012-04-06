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
    qt = require('..');

var app = new qt.QApplication();

// Constructor with numeric RGB
{
  var color = new qt.QColor(255, 155, 55);
  assert.equal(color.red(), 255);
  assert.equal(color.green(), 155);
  assert.equal(color.blue(), 55);
  assert.equal(color.alpha(), 255);
}

// Constructor w/ numeric RGBA
{
  var color = new qt.QColor(255, 155, 55, 111);
  assert.equal(color.red(), 255);
  assert.equal(color.green(), 155);
  assert.equal(color.blue(), 55);
  assert.equal(color.alpha(), 111);
}

// Constructor w/ string (CSS-like)
{
  var color = new qt.QColor('#ff0f00');
  assert.equal(color.red(), 255);
  assert.equal(color.green(), 15);
  assert.equal(color.blue(), 0);
  assert.equal(color.alpha(), 255);
}

// Constructor from another QColor
{
  var color = new qt.QColor('#ff0f00');
  var color2 = new qt.QColor(color);
  assert.equal(color2.red(), 255);
  assert.equal(color2.green(), 15);
  assert.equal(color2.blue(), 0);
  assert.equal(color2.alpha(), 255);
}

// name()
{
  var color = new qt.QColor('blue');
  assert.equal(color.name(), '#0000ff');
}
