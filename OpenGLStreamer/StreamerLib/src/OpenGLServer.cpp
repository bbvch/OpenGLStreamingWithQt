/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#include "OpenGLServer.h"
#include "Events.h"

#include <QWebSocketServer>
#include <QCoreApplication>
#include <QWebSocket>
#include <QInputEvent>
#include <QDebug>

#include <tuple>
#include <cassert>

QT_USE_NAMESPACE

OpenGLServer::OpenGLServer(quint16 port, bool debug, QObject *parent) :
    OpenGLProxy(debug, parent),
    mObj(parent),
    mpWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    mClients(),
    mDebug(debug)
{
    if (mpWebSocketServer->listen(QHostAddress::Any, port)) {
        if (mDebug)
            qDebug() << "OpenGL server listening on port" << port;
        connect(mpWebSocketServer, &QWebSocketServer::newConnection,
                this, &OpenGLServer::onNewConnection);
        connect(mpWebSocketServer, &QWebSocketServer::closed, this, &OpenGLServer::closed);
        connect(this, &OpenGLProxy::glFunctionSerialized, this, &OpenGLServer::sendBinaryMessage);
    }
}

OpenGLServer::~OpenGLServer()
{
    mpWebSocketServer->close();
    qDeleteAll(mClients.begin(), mClients.end());
}

void OpenGLServer::onNewConnection()
{
    QWebSocket *pSocket = mpWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &OpenGLServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &OpenGLServer::socketDisconnected);

    mClients << pSocket;
}

void OpenGLServer::sendBinaryMessage(const QByteArray &message)
{
    foreach (QWebSocket *pClient, mClients) {
        pClient->sendBinaryMessage(message);
    }
}

void OpenGLServer::processBinaryMessage(const QByteArray &message)
{
    QInputEvent* event = mSerializer.deserializeEvent(message);
    assert(event != nullptr);
    assert(mObj != nullptr);

    qDebug() << "Posing event to" << mObj->metaObject()->className();
    qApp->postEvent(mObj, event);
}

void OpenGLServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (mDebug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        mClients.removeAll(pClient);
        pClient->deleteLater();
    }
}
