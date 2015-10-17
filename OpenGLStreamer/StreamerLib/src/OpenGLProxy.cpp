/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#include "OpenGLProxy.h"

#include <QDataStream>

#include <array>
#include <cassert>

#define CREATE_INVOKER(NAME) {#NAME, std::make_shared<FunctionCallResolver<1, decltype(&QOpenGLFunctions::NAME)>>(&QOpenGLFunctions::NAME, *this)}
#define CREATE_INVOKER_V(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), std::make_shared<FunctionCallResolver<VSIZE, decltype(&QOpenGLFunctions::NAME##VSIZE##DTYPE##v)>>(&QOpenGLFunctions::NAME##VSIZE##DTYPE##v, *this)}

OpenGLProxy::OpenGLProxy(ProxyType proxyType, bool debug, QObject *parent) :
    QObject(parent),
    mProxyType(proxyType),
    mDebug(debug),
    mOpenGLFunctionInvokers({CREATE_INVOKER(glClear),
                            CREATE_INVOKER_V(glUniformMatrix, 4, f),
                            CREATE_INVOKER(glUniform1i),
                            CREATE_INVOKER(glBindBuffer),
                            CREATE_INVOKER(glGetAttribLocation),
                            CREATE_INVOKER(glEnableVertexAttribArray),
                            CREATE_INVOKER(glVertexAttribPointer),
                            CREATE_INVOKER(glDrawElements),
                            CREATE_INVOKER(glGetUniformLocation)
                            }),
    mSerializer(debug)

{
    // TODO replace this with factory method
    if (mProxyType == eProxyServer)
        mpOpenGLServer.reset(new OpenGLServer(1234, mDebug));
    else if (mProxyType == eProxyClient)
    {
        mpOpenGLClient.reset(new OpenGLClient(QUrl(QStringLiteral("ws://localhost:1234")), mDebug));
        connect(mpOpenGLClient.get(), &OpenGLClient::binaryMessageReceived, this, &OpenGLProxy::onBinaryMessageReceived);
    }
}

void OpenGLProxy::initialize()
{
    initializeOpenGLFunctions();
}

void OpenGLProxy::onBinaryMessageReceived(const QByteArray &message)
{
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
