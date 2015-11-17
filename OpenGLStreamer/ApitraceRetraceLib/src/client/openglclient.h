/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLCLIENT_H
#define OPENGLCLIENT_H

#include <QWebSocket>

class OpenGLClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

private slots:
    void onConnected();
    void onDisconnected();
    void onBinaryMessageReceived(const QByteArray &message);

private:
    QWebSocket mWebSocket;
    QUrl mUrl;
    bool mDebug{false};
};

#endif // OPENGLCLIENT_H
