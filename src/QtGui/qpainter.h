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

#ifndef QPAINTERWRAP_H
#define QPAINTERWRAP_H

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <QPainter>

class QPainterWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QPainter* GetWrapped() const { return q_; };

 private:
  QPainterWrap();
  ~QPainterWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  //
  // Wrapped methods exposed to JS
  //

  static v8::Handle<v8::Value> Begin(const v8::Arguments& args);
  static v8::Handle<v8::Value> End(const v8::Arguments& args);
  static v8::Handle<v8::Value> IsActive(const v8::Arguments& args);
  static v8::Handle<v8::Value> Save(const v8::Arguments& args);
  static v8::Handle<v8::Value> Restore(const v8::Arguments& args);

  // State
  static v8::Handle<v8::Value> SetPen(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetFont(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetMatrix(const v8::Arguments& args);

  // Paint actions
  static v8::Handle<v8::Value> FillRect(const v8::Arguments& args);
  static v8::Handle<v8::Value> DrawText(const v8::Arguments& args);
  static v8::Handle<v8::Value> DrawPixmap(const v8::Arguments& args);
  static v8::Handle<v8::Value> DrawImage(const v8::Arguments& args);
  static v8::Handle<v8::Value> StrokePath(const v8::Arguments& args);

  // Wrapped object
  QPainter* q_;
};

#endif
