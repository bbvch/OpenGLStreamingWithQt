/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLSERVER_H
#define OPENGLSERVER_H

#include <QList>

#include "Singleton.h"
#include "OpenGLProxy.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QByteArray)

#define OPENGL_CALL(TYPE, NAME, ...) Singleton<OpenGLServer>::instance().glCall(TYPE, &QOpenGLFunctions_ES2::NAME, #NAME, 0, __VA_ARGS__)
#define OPENGL_CALL_ARRAY(TYPE, NAME, ASIZE, ...) Singleton<OpenGLServer>::instance().glCall(TYPE, &QOpenGLFunctions_ES2::NAME, #NAME, ASIZE, __VA_ARGS__)
#define OPENGL_CALL_VECTOR(TYPE, NAME, VSIZE, DTYPE, ...) Singleton<OpenGLServer>::instance().glCall(TYPE, &QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v, STRINGIFY(NAME##VSIZE##DTYPE##v), VSIZE, __VA_ARGS__)
#define OPENGL_CALL_MATRIX(TYPE, NAME, VSIZE, DTYPE, ...) Singleton<OpenGLServer>::instance().glCall(TYPE, &QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v, STRINGIFY(NAME##VSIZE##DTYPE##v), VSIZE*VSIZE, __VA_ARGS__)

class OpenGLServer : public OpenGLProxy
{
    Q_OBJECT
private:
    explicit OpenGLServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
public:
    ~OpenGLServer();

    static OpenGLServer &get()
    {
        return Singleton<OpenGLServer>::instance();
    }

signals:
    void closed();

private slots:
    void onNewConnection();
    void processBinaryMessage(const QByteArray &message);
    void socketDisconnected();
    void sendBinaryMessage(const QByteArray &message);

private:
    void updateWidgets();
    void sendOpenGLInitialization();
    void sendOpenGLBufferObject(quint32 target, quint32 binding);
    void sendOpenGLTexture();

private:
    QWebSocketServer *mpWebSocketServer;
    QList<QWebSocket *> mClients;
    bool mDebug{false};

    template <typename T>
    friend class Singleton;
};

#endif //OPENGLSERVER_H
