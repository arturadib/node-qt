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
#include "../QtCore/qsize.h"
#include "qwidget.h"
#include "qmouseevent.h"
#include "qkeyevent.h"

using namespace v8;

Persistent<Function> QWidgetWrap::constructor;

//
// QWidgetImpl()
//

QWidgetImpl::QWidgetImpl(QWidgetImpl* parent) : QWidget(parent) {
  // Initialize callbacks as boolean values so we can test if the callback
  // has been set via ->IsFunction() below
  paintEventCallback_ = Persistent<Boolean>::New(Boolean::New(false));
  mousePressCallback_ = Persistent<Boolean>::New(Boolean::New(false));
  mouseReleaseCallback_ = Persistent<Boolean>::New(Boolean::New(false));
  mouseMoveCallback_ = Persistent<Boolean>::New(Boolean::New(false));
  keyPressCallback_ = Persistent<Boolean>::New(Boolean::New(false));
  keyReleaseCallback_ = Persistent<Boolean>::New(Boolean::New(false));
}

QWidgetImpl::~QWidgetImpl() {
  paintEventCallback_.Dispose();
  mousePressCallback_.Dispose();
  mouseReleaseCallback_.Dispose();
  mouseMoveCallback_.Dispose();
  keyPressCallback_.Dispose();
  keyReleaseCallback_.Dispose();
}

void QWidgetImpl::paintEvent(QPaintEvent* e) {
  HandleScope scope;
  
  if (!paintEventCallback_->IsFunction())
    return;

  const unsigned argc = 0;
  Handle<Value> argv[1] = {};
  Handle<Function> cb = Persistent<Function>::Cast(paintEventCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::mousePressEvent(QMouseEvent* e) {
  e->ignore(); // ensures event bubbles up

  HandleScope scope;
  
  if (!mousePressCallback_->IsFunction())
    return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mousePressCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::mouseReleaseEvent(QMouseEvent* e) {
  e->ignore(); // ensures event bubbles up

  HandleScope scope;
  
  if (!mouseReleaseCallback_->IsFunction())
    return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mouseReleaseCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::mouseMoveEvent(QMouseEvent* e) {
  e->ignore(); // ensures event bubbles up

  HandleScope scope;
  
  if (!mouseMoveCallback_->IsFunction())
    return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QMouseEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(mouseMoveCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::keyPressEvent(QKeyEvent* e) {
  e->ignore(); // ensures event bubbles up

  HandleScope scope;
  
  if (!keyPressCallback_->IsFunction())
    return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QKeyEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(keyPressCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

void QWidgetImpl::keyReleaseEvent(QKeyEvent* e) {
  e->ignore(); // ensures event bubbles up

  HandleScope scope;
  
  if (!keyReleaseCallback_->IsFunction())
    return;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = {
    QKeyEventWrap::NewInstance(*e)
  };
  Handle<Function> cb = Persistent<Function>::Cast(keyReleaseCallback_);
    
  cb->Call(Context::GetCurrent()->Global(), argc, argv);
}

//
// QWidgetWrap()
//

QWidgetWrap::QWidgetWrap(QWidgetImpl* parent) {
  q_ = new QWidgetImpl(parent);
}

QWidgetWrap::~QWidgetWrap() {
  delete q_;
}

void QWidgetWrap::Initialize(Handle<Object> target) {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("QWidget"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);  

  // Wrapped methods
  tpl->PrototypeTemplate()->Set(String::NewSymbol("resize"),
      FunctionTemplate::New(Resize)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("show"),
      FunctionTemplate::New(Show)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("size"),
      FunctionTemplate::New(Size)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("width"),
      FunctionTemplate::New(Width)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("height"),
      FunctionTemplate::New(Height)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("parent"),
      FunctionTemplate::New(Parent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("objectName"),
      FunctionTemplate::New(ObjectName)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setObjectName"),
      FunctionTemplate::New(SetObjectName)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("update"),
      FunctionTemplate::New(Update)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("hasMouseTracking"),
      FunctionTemplate::New(HasMouseTracking)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setMouseTracking"),
      FunctionTemplate::New(SetMouseTracking)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setFocusPolicy"),
      FunctionTemplate::New(SetFocusPolicy)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("move"),
      FunctionTemplate::New(Move)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("x"),
      FunctionTemplate::New(X)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("y"),
      FunctionTemplate::New(Y)->GetFunction());

  // Events
  tpl->PrototypeTemplate()->Set(String::NewSymbol("paintEvent"),
      FunctionTemplate::New(PaintEvent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("mousePressEvent"),
      FunctionTemplate::New(MousePressEvent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("mouseReleaseEvent"),
      FunctionTemplate::New(MouseReleaseEvent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("mouseMoveEvent"),
      FunctionTemplate::New(MouseMoveEvent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("keyPressEvent"),
      FunctionTemplate::New(KeyPressEvent)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("keyReleaseEvent"),
      FunctionTemplate::New(KeyReleaseEvent)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
  target->Set(String::NewSymbol("QWidget"), constructor);
}

Handle<Value> QWidgetWrap::New(const Arguments& args) {
  HandleScope scope;
  QWidgetImpl* q_parent = 0;

  if (args.Length() > 0) {
    QWidgetWrap* w_parent = node::ObjectWrap::Unwrap<QWidgetWrap>(args[0]->ToObject());
    q_parent = w_parent->GetWrapped();
  }

  QWidgetWrap* w = new QWidgetWrap(q_parent);
  w->Wrap(args.This());

  return args.This();
}

Handle<Value> QWidgetWrap::Resize(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->resize(args[0]->NumberValue(), args[1]->NumberValue());

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::Show(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->show();

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::Close(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->close();

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::Size(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close( QSizeWrap::NewInstance(q->size()) );
}

Handle<Value> QWidgetWrap::Width(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close( Integer::New(q->width()) );
}

Handle<Value> QWidgetWrap::Height(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close( Integer::New(q->height()) );
}

Handle<Value> QWidgetWrap::ObjectName(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(qt_v8::FromQString(q->objectName()));
}

Handle<Value> QWidgetWrap::SetObjectName(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setObjectName(qt_v8::ToQString(args[0]->ToString()));

  return scope.Close(Undefined());
}

//
// QUIRK:
// Here: Parent() returns the parent's name
// Qt: Parent() returns QObject
// Intended mostly for sanity checks
//
Handle<Value> QWidgetWrap::Parent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(qt_v8::FromQString(q->parent()->objectName()));
}

//
// PaintEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::PaintEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->paintEventCallback_.Dispose();
  q->paintEventCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

//
// MousePressEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::MousePressEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mousePressCallback_.Dispose();
  q->mousePressCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

//
// MouseReleaseEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::MouseReleaseEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mouseReleaseCallback_.Dispose();
  q->mouseReleaseCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

//
// MouseMoveEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::MouseMoveEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->mouseMoveCallback_.Dispose();
  q->mouseMoveCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

//
// KeyPressEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::KeyPressEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->keyPressCallback_.Dispose();
  q->keyPressCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

//
// KeyReleaseEvent()
// Binds a callback to Qt's event
//
Handle<Value> QWidgetWrap::KeyReleaseEvent(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->keyReleaseCallback_.Dispose();
  q->keyReleaseCallback_ = Persistent<Function>::New(
      Local<Function>::Cast(args[0]));

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::Update(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->update();

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::HasMouseTracking(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(Boolean::New(q->hasMouseTracking()));
}

Handle<Value> QWidgetWrap::SetMouseTracking(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setMouseTracking(args[0]->BooleanValue());

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::SetFocusPolicy(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->setFocusPolicy((Qt::FocusPolicy)(args[0]->IntegerValue()));

  return scope.Close(Undefined());
}

// Supported implementations:
//    move (int x, int y)
Handle<Value> QWidgetWrap::Move(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  q->move(args[0]->IntegerValue(), args[1]->IntegerValue());

  return scope.Close(Undefined());
}

Handle<Value> QWidgetWrap::X(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(Integer::New(q->x()));
}

Handle<Value> QWidgetWrap::Y(const Arguments& args) {
  HandleScope scope;

  QWidgetWrap* w = node::ObjectWrap::Unwrap<QWidgetWrap>(args.This());
  QWidgetImpl* q = w->GetWrapped();

  return scope.Close(Integer::New(q->y()));
}
