#include "OpenGLClient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &OpenGLClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &OpenGLClient::closed);
    m_webSocket.open(QUrl(url));
}

void OpenGLClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &OpenGLClient::onBinaryMessageReceived);
}

void OpenGLClient::onBinaryMessageReceived(const QByteArray &message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
}
