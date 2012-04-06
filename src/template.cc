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
#include "__template__.h"

using namespace v8;

Persistent<Function> __Template__Wrap::constructor;

// Supported implementations:
//   __Template__ ( ??? )
__Template__Wrap::__Template__Wrap(const Arguments& args) : q_(NULL) {
  q_ = new __Template__;
}

__Template__Wrap::~__Template__Wrap() {
  delete q_;
}

void __Template__Wrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("__Template__"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("example"),
      FunctionTemplate::New(Example)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("__Template__"), constructor);
}

Handle<Value> __Template__Wrap::New(const Arguments& args) {
  HandleScope scope;

  __Template__Wrap* w = new __Template__Wrap(args);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> __Template__Wrap::NewInstance(__Template__ q) {
  HandleScope scope;
  
  Local<Object> instance = constructor->NewInstance(0, NULL);
  __Template__Wrap* w = node::ObjectWrap::Unwrap<__Template__Wrap>(instance);
  w->SetWrapped(q);

  return scope.Close(instance);
}

Handle<Value> __Template__Wrap::Example(const Arguments& args) {
  HandleScope scope;

  __Template__Wrap* w = ObjectWrap::Unwrap<__Template__Wrap>(args.This());
  __Template__* q = w->GetWrapped();

  // q->...?

  return scope.Close(Undefined());
}
