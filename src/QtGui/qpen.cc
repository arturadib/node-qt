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

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "../qt_v8.h"
#include "qpen.h"
#include "qbrush.h"
#include "qcolor.h"

using namespace v8;

Persistent<Function> QPenWrap::constructor;

// Supported implementations:
//   QPen (QBrush brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin )
//   QPen (QColor color)
//   QPen ()
QPenWrap::QPenWrap(const Arguments& args) {
  QString arg0_constructor;
  if (args[0]->IsObject()) {
    arg0_constructor = 
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());
  }

  if (!args[0]->IsObject()) {
    // QPen ()
  
    q_ = new QPen();
    return;
  }

  if (arg0_constructor == "QColor") {
    // QPen (QColor color)

    // Unwrap QColor
    QColorWrap* color_wrap = ObjectWrap::Unwrap<QColorWrap>(
        args[0]->ToObject());
    QColor* color = color_wrap->GetWrapped();

    q_ = new QPen(*color);
    return;
  } else if (arg0_constructor == "QBrush") {    
    // QPen (QBrush brush, qreal width, Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin )
    
    // Unwrap QBrush
    QBrushWrap* brush_wrap = ObjectWrap::Unwrap<QBrushWrap>(
        args[0]->ToObject());
    QBrush* brush = brush_wrap->GetWrapped();

    qreal width(args[1]->NumberValue());

    if (args.Length() == 2) {
      q_ = new QPen(*brush, width);
      return;
    }

    if (args.Length() == 3) {
      Qt::PenStyle style((Qt::PenStyle)args[2]->IntegerValue());

      q_ = new QPen(*brush, width, style);
      return;
    }

    if (args.Length() == 4) {
      Qt::PenStyle style((Qt::PenStyle)args[2]->IntegerValue());
      Qt::PenCapStyle cap((Qt::PenCapStyle)args[3]->IntegerValue());

      q_ = new QPen(*brush, width, style, cap);
      return;
    }

    if (args.Length() == 5) {
      Qt::PenStyle style((Qt::PenStyle)args[2]->IntegerValue());
      Qt::PenCapStyle cap((Qt::PenCapStyle)args[3]->IntegerValue());
      Qt::PenJoinStyle join((Qt::PenJoinStyle)args[4]->IntegerValue());

      q_ = new QPen(*brush, width, style, cap, join);
      return;
    }
  } // QPen (QBrush, ...)
}

QPenWrap::~QPenWrap() {
  delete q_;
}

void QPenWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QPen"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QPen"), constructor);
}

Handle<Value> QPenWrap::New(const Arguments& args) {
  HandleScope scope;

  QPenWrap* w = new QPenWrap(args);
  w->Wrap(args.This());

  return args.This();
}
