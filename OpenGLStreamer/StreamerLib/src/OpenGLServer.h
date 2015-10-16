#ifndef OPENGLSERVER_H
#define OPENGLSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class OpenGLServer : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~OpenGLServer();

    void sendBinaryMessage(const QByteArray &message);

signals:
    void closed();

private slots:
    void onNewConnection();
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *mpWebSocketServer;
    QList<QWebSocket *> mClients;
    bool mDebug;
};

#endif //OPENGLSERVER_H
