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
#include "../QtGui/qwidget.h"
#include "qtesteventlist.h"

using namespace v8;

Persistent<Function> QTestEventListWrap::constructor;

QTestEventListWrap::QTestEventListWrap() {
  q_ = new QTestEventList();
}

QTestEventListWrap::~QTestEventListWrap() {
  delete q_;
}

void QTestEventListWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QTestEventList"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addMouseClick"),
      FunctionTemplate::New(AddMouseClick)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addKeyPress"),
      FunctionTemplate::New(AddKeyPress)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("simulate"),
      FunctionTemplate::New(Simulate)->GetFunction());

  constructor = Persistent<Function>::New(
      tpl->GetFunction());
  target->Set(String::NewSymbol("QTestEventList"), constructor);
}

Handle<Value> QTestEventListWrap::New(const Arguments& args) {
  HandleScope scope;

  QTestEventListWrap* w = new QTestEventListWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QTestEventListWrap::AddMouseClick(const Arguments& args) {
  HandleScope scope;

  QTestEventListWrap* w = ObjectWrap::Unwrap<QTestEventListWrap>(args.This());
  QTestEventList* q = w->GetWrapped();

  q->addMouseClick((Qt::MouseButton)args[0]->IntegerValue());

  return scope.Close(Undefined());
}

Handle<Value> QTestEventListWrap::AddKeyPress(const Arguments& args) {
  HandleScope scope;

  QTestEventListWrap* w = ObjectWrap::Unwrap<QTestEventListWrap>(args.This());
  QTestEventList* q = w->GetWrapped();

  if (args[0]->IsString())
    q->addKeyPress( qt_v8::ToQString(args[0]->ToString())[0].toAscii() );
  else
    q->addKeyPress( (Qt::Key)args[0]->IntegerValue() );

  return scope.Close(Undefined());
}

Handle<Value> QTestEventListWrap::Simulate(const Arguments& args) {
  HandleScope scope;

  QTestEventListWrap* w = ObjectWrap::Unwrap<QTestEventListWrap>(args.This());
  QTestEventList* q = w->GetWrapped();

  QWidgetWrap* widget_wrap = node::ObjectWrap::Unwrap<QWidgetWrap>(
      args[0]->ToObject());
  QWidget* widget = widget_wrap->GetWrapped();

  q->simulate(widget);

  return scope.Close(Undefined());
}
