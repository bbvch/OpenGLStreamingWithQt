#include "Channel.h"

Channel::Channel(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    mDebug(debug)
{
  if (mDebug)
      qDebug() << "WebSocket server:" << url;
  connect(&mWebSocket, &QWebSocket::connected, this, &Channel::onConnected);
  connect(&mWebSocket, &QWebSocket::disconnected, this, &Channel::onDisconnected);
  mWebSocket.open(QUrl(url));
}

void Channel::sendMessage(QByteArray &data)
{
    if (mWebSocket.isValid())
        mWebSocket.sendBinaryMessage(data);
}

void Channel::onConnected()
{
    if (mDebug)
        qDebug() << "WebSocket connected";

    connect(&mWebSocket, &QWebSocket::binaryMessageReceived, this, &Channel::messageReceived);
}

void Channel::onDisconnected()
{
    if (mDebug)
        qDebug() << "WebSocket connected";

    emit closed();
}

bool Channel::isValid()
{
    return mWebSocket.isValid();
}
