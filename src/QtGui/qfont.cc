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
#include "qfont.h"
#include "../qt_v8.h"

using namespace v8;

Persistent<Function> QFontWrap::constructor;

// Supported implementations:
//   QFont ( )
//   QFont ( const QString & family, int pointSize = -1, int weight = -1, 
//     bool italic = false )
//   QFont ( QFont font )
QFontWrap::QFontWrap(const Arguments& args) : q_(NULL) {
  if (args.Length() == 0) {
    // QFont ()

    q_ = new QFont;
    return;
  }

  // QFont ( QFont font )

  if (args.Length() == 1 && args[0]->IsObject()) {
    QString arg0_constructor = 
        qt_v8::ToQString(args[0]->ToObject()->GetConstructorName());

    if (arg0_constructor != "QFont")
      ThrowException(Exception::TypeError(
        String::New("QFont::QFont: bad argument")));

    // Unwrap obj
    QFontWrap* q_wrap = ObjectWrap::Unwrap<QFontWrap>(
        args[0]->ToObject());
    QFont* q = q_wrap->GetWrapped();

    q_ = new QFont(*q);
  }

  // QFont ( const QString & family, int pointSize = -1, int weight = -1, 
  //   bool italic = false )

  if (args.Length() == 1 && args[0]->IsString()) {
    q_ = new QFont(qt_v8::ToQString(args[0]->ToString()));
    return;
  }

  if (args.Length() == 2) {
    q_ = new QFont(qt_v8::ToQString(args[0]->ToString()), 
        args[1]->IntegerValue());
    return;
  }

  if (args.Length() == 3) {
    q_ = new QFont(qt_v8::ToQString(args[0]->ToString()), 
        args[1]->IntegerValue(), args[2]->IntegerValue());
    return;
  }

  if (args.Length() == 4) {
    q_ = new QFont(qt_v8::ToQString(args[0]->ToString()), 
        args[1]->IntegerValue(), args[2]->IntegerValue(),
        args[3]->BooleanValue());
    return;
  }
}

QFontWrap::~QFontWrap() {
  delete q_;
}

void QFontWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QFont"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setFamily"),
      FunctionTemplate::New(SetFamily)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("family"),
      FunctionTemplate::New(Family)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPixelSize"),
      FunctionTemplate::New(SetPixelSize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("pixelSize"),
      FunctionTemplate::New(PixelSize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPointSize"),
      FunctionTemplate::New(SetPointSize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("pointSize"),
      FunctionTemplate::New(PointSize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setPointSizeF"),
      FunctionTemplate::New(SetPointSizeF)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("pointSizeF"),
      FunctionTemplate::New(PointSizeF)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QFont"), constructor);
}

Handle<Value> QFontWrap::New(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = new QFontWrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QFontWrap::NewInstance(QFont q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  QFontWrap* w = node::ObjectWrap::Unwrap<QFontWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

Handle<Value> QFontWrap::SetFamily(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  q->setFamily(qt_v8::ToQString(args[0]->ToString()));

  return scope.Close(Undefined());
}

Handle<Value> QFontWrap::Family(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  return scope.Close(qt_v8::FromQString(q->family()));
}

Handle<Value> QFontWrap::SetPixelSize(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  q->setPixelSize(args[0]->IntegerValue());

  return scope.Close(Undefined());
}

Handle<Value> QFontWrap::PixelSize(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  return scope.Close(Number::New(q->pixelSize()));
}

Handle<Value> QFontWrap::SetPointSize(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  q->setPointSize(args[0]->IntegerValue());

  return scope.Close(Undefined());
}

Handle<Value> QFontWrap::PointSize(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  return scope.Close(Number::New(q->pointSize()));
}

Handle<Value> QFontWrap::SetPointSizeF(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  q->setPointSizeF(args[0]->NumberValue());

  return scope.Close(Undefined());
}

Handle<Value> QFontWrap::PointSizeF(const Arguments& args) {
  HandleScope scope;

  QFontWrap* w = ObjectWrap::Unwrap<QFontWrap>(args.This());
  QFont* q = w->GetWrapped();

  return scope.Close(Number::New(q->pointSizeF()));
}
