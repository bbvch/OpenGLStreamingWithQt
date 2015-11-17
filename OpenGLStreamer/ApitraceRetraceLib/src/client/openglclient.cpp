/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#include "openglclient.h"

#include <QDebug>
#include <QDataStream>

#include <retrace_main.hpp>

#include <cassert>

QT_USE_NAMESPACE

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    mUrl(url),
    mDebug(debug)
{
    retrace::init();

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
    if (mDebug)
        qDebug() << "New messages received. Size: " << message.length();

    retrace::processCall(message.constData(), message.length());
}
