#include "OpenGLServer.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

OpenGLServer::OpenGLServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
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

void OpenGLServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (mDebug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
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
