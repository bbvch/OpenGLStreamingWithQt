#include "OpenGLClient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

GlClient::GlClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &GlClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &GlClient::closed);
    m_webSocket.open(QUrl(url));
}

void GlClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &GlClient::onBinaryMessageReceived);
}

void GlClient::onBinaryMessageReceived(const QByteArray &message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
}
