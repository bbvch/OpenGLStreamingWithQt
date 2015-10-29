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
#include <QByteArray>
#include <QDebug>

#include <tuple>
#include <cassert>

QT_USE_NAMESPACE

OpenGLServer::OpenGLServer(quint16 port, bool debug, QObject *parent) :
    OpenGLProxy(debug, parent),
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

    sendOpenGLBufferObjects();
    updateWidgets();
}

void OpenGLServer::updateWidgets()
{
    foreach (QOpenGLWidget *pWidget, mWidgets) {
        pWidget->update();
    }
}

void OpenGLServer::sendOpenGLBufferObjects()
{
    mWidgets.first()->makeCurrent();

    sendBufferObject(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING);
    sendBufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING);

    mWidgets.first()->doneCurrent();
}

void OpenGLServer::sendBufferObject(quint32 target, quint32 binding)
{
    GLint bufferId;
    GLint access, mapped, size, usage;
    OPENGL_CALL(eServerCall, glGetIntegerv, binding, &bufferId);
    OPENGL_CALL(eServerCall, glGetBufferParameteriv, target, GL_BUFFER_ACCESS, &access);
    OPENGL_CALL(eServerCall, glGetBufferParameteriv, target, GL_BUFFER_MAPPED, &mapped);
    OPENGL_CALL(eServerCall, glGetBufferParameteriv, target, GL_BUFFER_SIZE, &size);
    OPENGL_CALL(eServerCall, glGetBufferParameteriv, target, GL_BUFFER_USAGE, &usage);

    if (bufferId > 0 && size > 0)
    {
        quint8 *data;
        data = new quint8 [size];
        OPENGL_CALL(eServerCall, glGetBufferSubData, target, 0, size, data);
        OPENGL_CALL(eClientCall, glBindBuffer, target, bufferId);
        OPENGL_CALL_ARRAY(eClientCall, glBufferData, size, target, size, data, usage);
        delete[] data;
    }
}

void OpenGLServer::sendBinaryMessage(const QByteArray &message)
{
    foreach (QWebSocket *pClient, mClients) {
        pClient->sendBinaryMessage(message);
    }
}

void OpenGLServer::processBinaryMessage(const QByteArray &message)
{
    Archive ar(message);

    if (QObject *obj = findOpenGLWidget(ar.getData().constData()))
    {
        QEvent* event = mSerializer.deserialize(ar);
        assert(event != nullptr);
        if (mDebug)
            qDebug() << "Posting event to" << obj->metaObject()->className();
        qApp->postEvent(obj, event);
    }
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
