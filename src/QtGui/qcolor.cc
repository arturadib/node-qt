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
#include "qcolor.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QColorWrap::constructor;

// Supported implementations:
//   QColor ( int r, int g, int b, int a = 255 )
//   QColor ( QString color )
//   QColor ( QColor )
QColorWrap::QColorWrap(const Arguments& args) {
  if (args.Length() >= 3) {
    // QColor ( int r, int g, int b, int a = 255 )
    q_ = new QColor(
        args[0]->IntegerValue(), 
        args[1]->IntegerValue(),
        args[2]->IntegerValue(), 
        args[3]->IsNumber() ? args[3]->IntegerValue() : 255
    );
  } else if (args[0]->IsString()) {
    // QColor ( QString color )
    q_ = new QColor( qt_v8::ToQString(args[0]->ToString()) );
  } else if (args[0]->IsObject()) {
    // QColor ( QColor color )
    QString arg0_constructor = 
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());

    if (arg0_constructor != "QColor")
      ThrowException(Exception::TypeError(
        String::New("QColor::QColor: bad argument")));

    // Unwrap obj
    QColorWrap* q_wrap = ObjectWrap::Unwrap<QColorWrap>(
        args[0]->ToObject());
    QColor* q = q_wrap->GetWrapped();

    q_ = new QColor(*q);
  }
}

QColorWrap::~QColorWrap() {
  delete q_;
}

void QColorWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QColor"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("red"),
      FunctionTemplate::New(Red)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("green"),
      FunctionTemplate::New(Green)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("blue"),
      FunctionTemplate::New(Blue)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("alpha"),
      FunctionTemplate::New(Alpha)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("name"),
      FunctionTemplate::New(Name)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QColor"), constructor);
}

Handle<Value> QColorWrap::New(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = new QColorWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QColorWrap::Red(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = ObjectWrap::Unwrap<QColorWrap>(args.This());
  QColor* q = w->GetWrapped();

  return scope.Close(Number::New(q->red()));
}

Handle<Value> QColorWrap::Green(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = ObjectWrap::Unwrap<QColorWrap>(args.This());
  QColor* q = w->GetWrapped();

  return scope.Close(Number::New(q->green()));
}

Handle<Value> QColorWrap::Blue(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = ObjectWrap::Unwrap<QColorWrap>(args.This());
  QColor* q = w->GetWrapped();

  return scope.Close(Number::New(q->blue()));
}

Handle<Value> QColorWrap::Alpha(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = ObjectWrap::Unwrap<QColorWrap>(args.This());
  QColor* q = w->GetWrapped();

  return scope.Close(Number::New(q->alpha()));
}

Handle<Value> QColorWrap::Name(const Arguments& args) {
  HandleScope scope;

  QColorWrap* w = ObjectWrap::Unwrap<QColorWrap>(args.This());
  QColor* q = w->GetWrapped();

  QString name = q->name();

  return scope.Close(qt_v8::FromQString(name));
}
