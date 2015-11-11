/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#include "openglclient.h"

#include <QDebug>
#include <QDataStream>

#include <cassert>

QT_USE_NAMESPACE

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    mUrl(url),
    mDebug(debug)
{
    if (mDebug)
        qDebug() << "OpenGL client:" << url;
    QObject::connect(&mWebSocket, &QWebSocket::connected, this, &OpenGLClient::onConnected);
    QObject::connect(&mWebSocket, &QWebSocket::disconnected, this, &OpenGLClient::onDisconnected);

    mWebSocket.open(QUrl(url));
}

void OpenGLClient::onConnected()
{
    if (mDebug)
        qDebug() << "WebSocket connected";
    QObject::connect(&mWebSocket, &QWebSocket::binaryMessageReceived,
            this, &OpenGLClient::onBinaryMessageReceived);
}

void OpenGLClient::onDisconnected()
{
}

void OpenGLClient::onBinaryMessageReceived(const QByteArray &message)
{
    mMessageQueue.enqueue(message);
    if (mDebug)
        qDebug() << "Queue size:" << mMessageQueue.size();
}

void OpenGLClient::update()
{
    while (!mMessageQueue.isEmpty())
    {
        QByteArray message = mMessageQueue.takeFirst();

        if (mDebug)
            qDebug() << "Message recieved:" << message;
    }
}
