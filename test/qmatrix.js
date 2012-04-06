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
  var matrix = new qt.QMatrix;
  assert.ok(matrix);
}

// Constructor: components
{
  var matrix = new qt.QMatrix(1, 2, 3, 4, 5, 6);
  assert.ok(matrix);

  assert.equal(matrix.m11(), 1);
  assert.equal(matrix.m12(), 2);
  assert.equal(matrix.m21(), 3);
  assert.equal(matrix.m22(), 4);
  assert.equal(matrix.dx(), 5);
  assert.equal(matrix.dy(), 6);

  assert.equal(matrix.translate(0, 0), matrix);
  assert.equal(matrix.scale(1, 1), matrix);
}

// Constructor: another QMatrix
{
  var matrix = new qt.QMatrix(1, 2, 3, 4, 5, 6);
  var matrix2 = new qt.QMatrix(matrix);

  assert.equal(matrix2.m11(), 1);
  assert.equal(matrix2.m12(), 2);
  assert.equal(matrix2.m21(), 3);
  assert.equal(matrix2.m22(), 4);
  assert.equal(matrix2.dx(), 5);
  assert.equal(matrix2.dy(), 6);

  matrix.translate(123, 123);

  // matrix.translate shouldn't affect matrix2
  assert.equal(matrix2.m11(), 1);
  assert.equal(matrix2.m12(), 2);
  assert.equal(matrix2.m21(), 3);
  assert.equal(matrix2.m22(), 4);
  assert.equal(matrix2.dx(), 5);
  assert.equal(matrix2.dy(), 6);
}
