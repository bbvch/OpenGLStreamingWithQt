/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLCLIENT_H
#define OPENGLCLIENT_H

#include "OpenGLProxy.h"

#include <QWebSocket>
#include <QHash>
#include <QQueue>

#include <memory>

class OpenGLClient : public OpenGLProxy
{
    Q_OBJECT
public:
    explicit OpenGLClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

    void update();
    bool updatedNeeded();

    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void onConnected();
    void onDisconnected();
    void onBinaryMessageReceived(const QByteArray &message);

private:
    QObject* mObj;
    QWebSocket mWebSocket;
    QUrl mUrl;
    bool mDebug;
    QHash<QString, std::shared_ptr<OpenGLProxy::FunctionInvoker>> mOpenGLFunctionInvokers;
    QQueue<QByteArray> mMessageQueue;

};

#endif // OPENGLCLIENT_H
