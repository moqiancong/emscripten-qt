/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATATRANSFERER_H
#define DATATRANSFERER_H

#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTcpSocket>
#include <QHttp>
#include <QDebug>

// Interface-class for data transferring object

class DataTransferer : public QObject
{
    Q_OBJECT
public:
    explicit DataTransferer(QObject *parent = 0);
    virtual ~DataTransferer() {
        if (m_dataTransferOngoing) {
            qDebug("BearerEx Warning: dataobjects transfer was ongoing when destroyed.");
        }
    }
    virtual bool transferData() = 0;
    bool dataTransferOngoing();

signals:
    void finished(quint32 errorCode, qint64 dataReceived, QString errorType);

public slots:

protected:
    bool m_dataTransferOngoing;
};


// Specializations/concrete classes

class DataTransfererQTcp : public DataTransferer
{
    Q_OBJECT
public:
    DataTransfererQTcp(QObject* parent = 0);
    ~DataTransfererQTcp();

    virtual bool transferData();

public slots:
    void readyRead();
    void error(QAbstractSocket::SocketError socketError);
    void connected();

private:
    QTcpSocket m_qsocket;
};

class DataTransfererQNam : public DataTransferer
{
    Q_OBJECT
public:
    DataTransfererQNam(QObject* parent = 0);
    ~DataTransfererQNam();

    virtual bool transferData();

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_qnam;
};

class DataTransfererQHttp : public DataTransferer
{
    Q_OBJECT
public:
    DataTransfererQHttp(QObject* parent = 0);
    ~DataTransfererQHttp();

    virtual bool transferData();

public slots:
    void done(bool error);

private:
    QHttp m_qhttp;
};

#endif // DATATRANSFERER_H
