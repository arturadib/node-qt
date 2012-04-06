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

// Constructor
{
  var font = new qt.QFont;
  assert.ok(font);
}

// Constructor- family
{
  var font = new qt.QFont('helvetica');
  assert.equal(font.family(), 'helvetica');
}

// Constructor- family, pointsize
{
  var font = new qt.QFont('helvetica', 12);
  assert.equal(font.pointSize(), 12);
}

// Constructor- from QFont
{
  var font = new qt.QFont('helvetica');
  var font2 = new qt.QFont(font);
  assert.equal(font2.family(), 'helvetica');
}

// setFamily()
{
  var font = new qt.QFont;
  font.setFamily('helvetica');
  assert.equal(font.family(), 'helvetica');
}

// pixelSize()
{
  var font = new qt.QFont;
  font.setPixelSize(12);
  assert.equal(font.pixelSize(), 12);
  font.setPixelSize(10.123);
  assert.equal(font.pixelSize(), 10);
}

// pointSizeF()
{
  var font = new qt.QFont;
  font.setPointSizeF(12.123);
  assert.equal(font.pointSizeF(), 12.123);
}
