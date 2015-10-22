/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLSERVER_H
#define OPENGLSERVER_H

#include <QList>
#include <QByteArray>

#include "OpenGLProxy.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class OpenGLServer : public OpenGLProxy
{
    Q_OBJECT
public:
    explicit OpenGLServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~OpenGLServer();

signals:
    void closed();

private slots:
    void onNewConnection();
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void sendBinaryMessage(const QByteArray &message);

private:
    QWebSocketServer *mpWebSocketServer;
    QList<QWebSocket *> mClients;
    bool mDebug;
};

#endif //OPENGLSERVER_H
