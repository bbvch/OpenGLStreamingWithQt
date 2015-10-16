#include "OpenGLClient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    mUrl(url),
    mDebug(debug)
{
    if (mDebug)
        qDebug() << "WebSocket server:" << url;
    connect(&mWebSocket, &QWebSocket::connected, this, &OpenGLClient::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &OpenGLClient::closed);
    mWebSocket.open(QUrl(url));
}

void OpenGLClient::onConnected()
{
    if (mDebug)
        qDebug() << "WebSocket connected";
    connect(&mWebSocket, &QWebSocket::binaryMessageReceived,
            this, &OpenGLClient::binaryMessageReceived);
}
