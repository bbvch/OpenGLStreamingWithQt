#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

    void sendMessage(QByteArray &data);
    bool isValid();

signals:
    void closed();
    void messageReceived(const QByteArray &message);

private slots:
    void onConnected();
    void onDisconnected();

private:
    QWebSocket mWebSocket;
    QUrl mUrl;
    bool mDebug;
};

#endif // CHANNEL_H
