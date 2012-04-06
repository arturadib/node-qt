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
#include "qmouseevent.h"

using namespace v8;

Persistent<Function> QMouseEventWrap::constructor;

QMouseEventWrap::QMouseEventWrap() : q_(NULL) {
  // Standalone constructor not implemented
  // Use SetWrapped()
}

QMouseEventWrap::~QMouseEventWrap() {
  delete q_;
}

void QMouseEventWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QMouseEvent"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  tpl->PrototypeTemplate()->Set(String::NewSymbol("x"),
      FunctionTemplate::New(X)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("y"),
      FunctionTemplate::New(Y)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("button"),
      FunctionTemplate::New(Button)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QMouseEvent"), constructor);
}

Handle<Value> QMouseEventWrap::New(const Arguments& args) {
  HandleScope scope;

  QMouseEventWrap* w = new QMouseEventWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QMouseEventWrap::NewInstance(QMouseEvent q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  QMouseEventWrap* w = node::ObjectWrap::Unwrap<QMouseEventWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

Handle<Value> QMouseEventWrap::X(const Arguments& args) {
  HandleScope scope;

  QMouseEventWrap* w = node::ObjectWrap::Unwrap<QMouseEventWrap>(args.This());
  QMouseEvent* q = w->GetWrapped();

  return scope.Close(Number::New(q->x()));
}

Handle<Value> QMouseEventWrap::Y(const Arguments& args) {
  HandleScope scope;

  QMouseEventWrap* w = node::ObjectWrap::Unwrap<QMouseEventWrap>(args.This());
  QMouseEvent* q = w->GetWrapped();

  return scope.Close(Number::New(q->y()));
}

Handle<Value> QMouseEventWrap::Button(const Arguments& args) {
  HandleScope scope;

  QMouseEventWrap* w = node::ObjectWrap::Unwrap<QMouseEventWrap>(args.This());
  QMouseEvent* q = w->GetWrapped();

  return scope.Close(Number::New(q->button()));
}
