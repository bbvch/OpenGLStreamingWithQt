#ifndef OPENGLCLIENT_H
#define OPENGLCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class OpenGLClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onBinaryMessageReceived(const QByteArray &message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // OPENGLCLIENT_H
