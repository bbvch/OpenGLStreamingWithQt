#ifndef OPENGLCLIENT_H
#define OPENGLCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class OpenGLClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

signals:
    void closed();
    void binaryMessageReceived(const QByteArray &message);

private slots:
    void onConnected();

private:
    QWebSocket mWebSocket;
    QUrl mUrl;
    bool mDebug;
};

#endif // OPENGLCLIENT_H
