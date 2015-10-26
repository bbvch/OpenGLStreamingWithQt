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

#define CREATE_INVOKER(NAME) {#NAME, std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME)>>(&QOpenGLFunctions_2_0::NAME, *this)}
#define CREATE_INVOKER_V(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v)>>(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, *this, VSIZE)}
#define CREATE_INVOKER_M(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v)>>(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, *this, VSIZE*VSIZE)}

OpenGLClient::OpenGLClient(const QUrl &url, bool debug, QObject *parent) :
    OpenGLProxy(debug, parent),
    mUrl(url),
    mDebug(debug),
    mOpenGLFunctionInvokers({CREATE_INVOKER(glClear),
                             CREATE_INVOKER_M(glUniformMatrix, 4, f),
                             CREATE_INVOKER(glUniform1i),
                             CREATE_INVOKER(glBindBuffer),
                             CREATE_INVOKER(glGetAttribLocation),
                             CREATE_INVOKER(glEnableVertexAttribArray),
                             CREATE_INVOKER(glVertexAttribPointer),
                             CREATE_INVOKER(glDrawElements),
                             CREATE_INVOKER(glGetUniformLocation),
                             CREATE_INVOKER(glBindTexture),
                             CREATE_INVOKER(glGetBufferSubData)
                            })
{
    if (mDebug)
        qDebug() << "WebSocket server:" << url;
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

    //mWebSocket.sendBinaryMessage(mSerializer.serialize(1, EventTypes::eUpdateEvent).getData());

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
    if (dynamic_cast<const QMouseEvent*>(ev) && findOpenGLWidget(obj->metaObject()->className()))
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

