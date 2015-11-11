/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLCLIENT_H
#define OPENGLCLIENT_H

#include <QWebSocket>
#include <QQueue>

class OpenGLClient : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

public:
    void update();
    bool updatedNeeded();

private slots:
    void onConnected();
    void onDisconnected();
    void onBinaryMessageReceived(const QByteArray &message);

private:
    QWebSocket mWebSocket;
    QUrl mUrl;
    bool mDebug{false};
    QQueue<QByteArray> mMessageQueue;
};

#endif // OPENGLCLIENT_H
