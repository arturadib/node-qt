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
#include "../QtCore/qsize.h"
#include "qresizeevent.h"

using namespace v8;

Persistent<Function> QResizeEventWrap::constructor;

QResizeEventWrap::QResizeEventWrap() : q_(NULL) {
  // Standalone constructor not implemented
  // Use SetWrapped()
}

QResizeEventWrap::~QResizeEventWrap() {
  delete q_;
}

void QResizeEventWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QResizeEvent"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->PrototypeTemplate()->Set(String::NewSymbol("accept"),
      FunctionTemplate::New(Accept)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("ignore"),
      FunctionTemplate::New(Ignore)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("isAccepted"),
      FunctionTemplate::New(IsAccepted)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setAccepted"),
      FunctionTemplate::New(SetAccepted)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("oldSize"),
      FunctionTemplate::New(OldSize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("size"),
      FunctionTemplate::New(Size)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QResizeEvent"), constructor);
}

Handle<Value> QResizeEventWrap::New(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = new QResizeEventWrap();
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QResizeEventWrap::NewInstance(QResizeEvent q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

Handle<Value> QResizeEventWrap::Accept(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  q->accept();

  return scope.Close(Undefined());
}

Handle<Value> QResizeEventWrap::Ignore(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  q->ignore();

  return scope.Close(Undefined());
}

Handle<Value> QResizeEventWrap::IsAccepted(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->isAccepted()));
}

Handle<Value> QResizeEventWrap::SetAccepted(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  q->setAccepted(args[0]->BooleanValue());

  return scope.Close(Undefined());
}

Handle<Value> QResizeEventWrap::Size(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  return scope.Close(QSizeWrap::NewInstance(q->size()));
}


Handle<Value> QResizeEventWrap::OldSize(const Arguments& args) {
  HandleScope scope;

  QResizeEventWrap* w = node::ObjectWrap::Unwrap<QResizeEventWrap>(args.This());
  QResizeEvent* q = w->GetWrapped();

  return scope.Close(QSizeWrap::NewInstance(q->oldSize()));
}
