/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLSERVER_H
#define OPENGLSERVER_H

#include <QList>

#include "OpenGLProxy.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QByteArray)

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
    void processBinaryMessage(const QByteArray &message);
    void socketDisconnected();
    void sendBinaryMessage(const QByteArray &message);

private:
    QObject* mObj{nullptr};
    QWebSocketServer *mpWebSocketServer;
    QList<QWebSocket *> mClients;
    bool mDebug{false};
};

#endif //OPENGLSERVER_H
