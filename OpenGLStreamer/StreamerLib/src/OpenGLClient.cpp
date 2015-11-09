/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#include "OpenGLClient.h"
#include "Events.h"

#include <QDebug>
#include <QApplication>
#include <QDataStream>
#include <QInputEvent>

#include <cassert>

QT_USE_NAMESPACE

#define CREATE_INVOKER(NAME) {#NAME, QSharedPointer<FunctionCallResolver<decltype(&QOpenGLFunctions_ES2::NAME)>>::create(&QOpenGLFunctions_ES2::NAME, *this)}
#define CREATE_INVOKER_ARRAY(NAME) {#NAME, QSharedPointer<FunctionCallResolver<decltype(&QOpenGLFunctions_ES2::NAME)>>::create(&QOpenGLFunctions_ES2::NAME, *this, 1)}
#define CREATE_INVOKER_VECTOR(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), QSharedPointer<FunctionCallResolver<decltype(&QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v)>>::create(&QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v, *this, VSIZE)}
#define CREATE_INVOKER_MATRIX(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), QSharedPointer<FunctionCallResolver<decltype(&QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v)>>::create(&QOpenGLFunctions_ES2::NAME##VSIZE##DTYPE##v, *this, VSIZE*VSIZE)}

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    OpenGLProxy(debug, parent),
    mUrl(url),
    mDebug(debug),
    mOpenGLFunctionInvokers({CREATE_INVOKER(glClear),
                             CREATE_INVOKER_MATRIX(glUniformMatrix, 4, f),
                             CREATE_INVOKER(glUniform1i),
                             CREATE_INVOKER(glBindBuffer),
                             CREATE_INVOKER(glGetAttribLocation),
                             CREATE_INVOKER(glEnableVertexAttribArray),
                             CREATE_INVOKER(glVertexAttribPointer),
                             CREATE_INVOKER(glDrawElements),
                             CREATE_INVOKER(glGetUniformLocation),
                             CREATE_INVOKER(glBindTexture),
                             CREATE_INVOKER_ARRAY(glBufferData)
                            })
{
    if (mDebug)
        qDebug() << "OpenGL client:" << url;
    QObject::connect(&mWebSocket, &QWebSocket::connected, this, &OpenGLClient::onConnected);
    QObject::connect(&mWebSocket, &QWebSocket::disconnected, this, &OpenGLClient::onDisconnected);

    mWebSocket.open(QUrl(url));
}

void OpenGLClient::onConnected()
{
    if (mDebug)
        qDebug() << "WebSocket connected";
    QObject::connect(&mWebSocket, &QWebSocket::binaryMessageReceived,
            this, &OpenGLClient::onBinaryMessageReceived);

    qApp->installEventFilter(this);
}

void OpenGLClient::onBinaryMessageReceived(const QByteArray &message)
{
    mMessageQueue.enqueue(message);
    if (mDebug)
        qDebug() << "Queue size:" << mMessageQueue.size();
}

void OpenGLClient::onDisconnected()
{
    qApp->removeEventFilter(this) ;
}

bool OpenGLClient::eventFilter(QObject *obj , QEvent *ev)
{
    if (!findOpenGLWidget(obj->metaObject()->className()))
        return false;

    if (dynamic_cast<const QMouseEvent*>(ev))
    {
        if (mDebug)
            qDebug() << "Serializing mouse event";

        const QMouseEvent& mouseEvent = *static_cast<const QMouseEvent*>(ev);

        Archive ar = mSerializer.serialize(1, obj->metaObject()->className(), EventTypes::eMouseEvent, mouseEvent.type(),
                                           mouseEvent.localPos(), mouseEvent.windowPos(), mouseEvent.screenPos(),
                                           mouseEvent.button(), mouseEvent.buttons(), mouseEvent.modifiers());
        mWebSocket.sendBinaryMessage(ar.getData());
    }

    return false;
}

void OpenGLClient::update()
{
    while (!mMessageQueue.isEmpty())
    {
        QByteArray message = mMessageQueue.takeFirst();

        QString funcName(message.data());

        if (mDebug)
            qDebug() << "OpenGL function" << funcName << "received";

        auto& invoker = mOpenGLFunctionInvokers[funcName];

        assert(invoker);

        if (invoker)
        {
            invoker->glCall(message);
        }
    }
}

bool OpenGLClient::updatedNeeded()
{
    return !mMessageQueue.isEmpty();
}

