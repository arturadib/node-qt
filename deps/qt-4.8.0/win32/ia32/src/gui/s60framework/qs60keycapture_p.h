/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Symbian application wrapper of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QS60KEYCAPTURE_P_H
#define QS60KEYCAPTURE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

#ifdef Q_OS_SYMBIAN

#include <QObject>
#include <QEvent>
#include <QTimer>
#include <remconcoreapitargetobserver.h>
#include <w32std.h>

class CRemConInterfaceSelector;
class CRemConCoreApiTarget;
class CResponseHandler;
class CCoeEnv;

QT_BEGIN_NAMESPACE

class QS60KeyCapture: public QObject,
                      public MRemConCoreApiTargetObserver
{
    Q_OBJECT
public:
    QS60KeyCapture(CCoeEnv *env, QObject *parent = 0);
    ~QS60KeyCapture();

    void MrccatoCommand(TRemConCoreApiOperationId operationId,
                        TRemConCoreApiButtonAction buttonAct);

private slots:
    void volumeUpClickTimerExpired();
    void volumeDownClickTimerExpired();
    void repeatTimerExpired();

private:
    void sendKey(TRemConCoreApiOperationId operationId, QEvent::Type type);
    TKeyEvent mapToKeyEvent(TRemConCoreApiOperationId operationId);
    void initRemCon();

private:
    QS60KeyCapture();
    Q_DISABLE_COPY(QS60KeyCapture)

    CCoeEnv *coeEnv;

    CRemConInterfaceSelector *selector;
    CRemConCoreApiTarget *target;
    CResponseHandler *handler;

    QTimer volumeUpClickTimer;
    QTimer volumeDownClickTimer;

    TKeyEvent repeatKeyEvent;
    int initialRepeatTime; // time before first repeat key event
    int repeatTime; // time between subsequent repeat key events
    QTimer repeatTimer;
};

QT_END_NAMESPACE

#endif // Q_OS_SYMBIAN
#endif // QS60KEYCAPTURE_P_H
