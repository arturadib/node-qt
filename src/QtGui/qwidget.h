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

#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H

#define BUILDING_NODE_EXTENSION
#include <node.h>
#include <QWidget>

//
// QWidgetImpl()
// Extends QWidget to implement virtual methods from QWidget
//
class QWidgetImpl : public QWidget {
 public:
  QWidgetImpl(QWidgetImpl* parent);
  ~QWidgetImpl();  
  v8::Persistent<v8::Value> paintEventCallback_;
  v8::Persistent<v8::Value> mousePressCallback_;
  v8::Persistent<v8::Value> mouseReleaseCallback_;
  v8::Persistent<v8::Value> mouseMoveCallback_;
  v8::Persistent<v8::Value> keyPressCallback_;
  v8::Persistent<v8::Value> keyReleaseCallback_;
  v8::Persistent<v8::Value> enterCallback_;
  v8::Persistent<v8::Value> leaveCallback_;
  v8::Persistent<v8::Value> closeCallback_;
  v8::Persistent<v8::Value> resizeCallback_;

 private:
  void paintEvent(QPaintEvent* e);
  void mousePressEvent(QMouseEvent* e);
  void mouseReleaseEvent(QMouseEvent* e);
  void mouseMoveEvent(QMouseEvent* e);
  void keyPressEvent(QKeyEvent* e);
  void keyReleaseEvent(QKeyEvent* e);
  void enterEvent(QEvent* e);
  void leaveEvent(QEvent* e);
  void closeEvent(QCloseEvent* e);
  void resizeEvent(QResizeEvent* e);
};

//
// QWidgetWrap()
//
class QWidgetWrap : public node::ObjectWrap {
 public:
  static void Initialize(v8::Handle<v8::Object> target);
  QWidgetImpl* GetWrapped() const { return q_; };

 private:
  QWidgetWrap(QWidgetImpl* parent);
  ~QWidgetWrap();
  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  // Wrapped methods
  static v8::Handle<v8::Value> Resize(const v8::Arguments& args);
  static v8::Handle<v8::Value> Show(const v8::Arguments& args);
  static v8::Handle<v8::Value> Close(const v8::Arguments& args);
  static v8::Handle<v8::Value> Size(const v8::Arguments& args);
  static v8::Handle<v8::Value> Width(const v8::Arguments& args);
  static v8::Handle<v8::Value> Height(const v8::Arguments& args);
  static v8::Handle<v8::Value> ObjectName(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetObjectName(const v8::Arguments& args);
  static v8::Handle<v8::Value> Parent(const v8::Arguments& args);
  static v8::Handle<v8::Value> Update(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetMouseTracking(const v8::Arguments& args);
  static v8::Handle<v8::Value> HasMouseTracking(const v8::Arguments& args);
  static v8::Handle<v8::Value> SetFocusPolicy(const v8::Arguments& args);
  static v8::Handle<v8::Value> Move(const v8::Arguments& args);
  static v8::Handle<v8::Value> X(const v8::Arguments& args);
  static v8::Handle<v8::Value> Y(const v8::Arguments& args);

  // QUIRK
  // Event binding. These functions bind implemented event handlers above
  // to the given callbacks. This is necessary as in Qt such handlers
  // are virtual and we can't dynamically implement them from JS
  static v8::Handle<v8::Value> PaintEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> MousePressEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> MouseReleaseEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> MouseMoveEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> KeyPressEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> KeyReleaseEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> EnterEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> LeaveEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> CloseEvent(const v8::Arguments& args);
  static v8::Handle<v8::Value> ResizeEvent(const v8::Arguments& args);

  // Wrapped object
  QWidgetImpl* q_;
};

#endif
