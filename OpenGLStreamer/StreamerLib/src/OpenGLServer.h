#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class GlServer : public QObject
{
    Q_OBJECT
public:
    explicit GlServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~GlServer();

    void sendBinaryMessage(const QByteArray &message);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *mpWebSocketServer;
    QList<QWebSocket *> mClients;
    bool mDebug;
};

#endif //ECHOSERVER_H
