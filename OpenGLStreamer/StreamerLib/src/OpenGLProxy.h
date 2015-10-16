/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QHash>

#include <memory>
#include <type_traits>

#include "Serializer.h"
#include "OpenGLServer.h"
#include "OpenGLClient.h"

#define STRINGIFY(STR) #STR
#define OPENGL_CALL(NAME, ...) mpOpenGLProxy->glCall<1>(&QOpenGLFunctions::NAME, #NAME, __VA_ARGS__)
#define OPENGL_CALL_V(NAME, VSIZE, DTYPE, ...) mpOpenGLProxy->glCall<VSIZE>(&QOpenGLFunctions::NAME##VSIZE##DTYPE##v, STRINGIFY(NAME##VSIZE##DTYPE##v), __VA_ARGS__)

namespace helper
{
    template<typename T>
    struct MethodTraits;

    template<class Class, typename Return, typename ... Args>
    struct MethodTraits<Return (Class::*)(Args...)>
    {
       using ClassType = Class;
       using ReturnType = Return;
       using MethodPtrType = Return (Class::*)(Args...);
       using ParameterType = std::tuple<Args...>;
       using Arity = std::tuple_size<ParameterType>;
    };

    template<std::size_t...S> struct seq
    {};

    template<std::size_t N, std::size_t ...S> struct gens : gens <N-1, N-1, S...>
    {};

    template<std::size_t ...S> struct gens<0, S...>
    {
       typedef seq<S...> type;
    };
}

class OpenGLProxy : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    enum ProxyType
    {
        eProxyServer,
        eProxyClient
    };

    explicit OpenGLProxy(ProxyType proxyType, bool debug = false, QObject *parent = 0);

    void initialize();

    template<std::size_t N, typename FunctionPtrType, typename... Args>
    typename std::enable_if<std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value, void>::type
    glCall(FunctionPtrType funcPtr, const char *funcName, Args &&...args)
    {
        using FunctionInfo = helper::MethodTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        callHelper<N>(funcPtr, funcName, std::move(params), s);
    }

    template<std::size_t N, typename FunctionPtrType, typename... Args>
    typename std::enable_if<!std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::MethodTraits<FunctionPtrType>::ReturnType>::type
    glCall(FunctionPtrType funcPtr, const char *funcName, Args &&...args)
    {
        using FunctionInfo = helper::MethodTraits<FunctionPtrType>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        return callHelper<N>(funcPtr, funcName, std::move(params), s);
    }

private:
    template<std::size_t N, typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    typename std::enable_if<std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value, void>::type
    callHelper(FunctionPtrType funcPtr, const char *funcName, ParameterType params, helper::seq<S...>)
    {
        (this->*funcPtr)(std::get<S>(params)...);
        if (mProxyType == eProxyServer && mpOpenGLServer)
        {
            mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(N, funcName, std::get<S>(params)...).getData());
        }
    }

    template<std::size_t N, typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    typename std::enable_if<!std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::MethodTraits<FunctionPtrType>::ReturnType>::type
    callHelper(FunctionPtrType funcPtr, const char *funcName, ParameterType params, helper::seq<S...>)
    {
        auto result = (this->*funcPtr)(std::get<S>(params)...);
        if (mProxyType == eProxyServer && mpOpenGLServer)
        {
            mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(N, funcName, std::get<S>(params)...).getData());
        }
        return result;
    }

    struct FunctionInvoker
    {
        virtual void glCall(const QByteArray &message) = 0;
    };

    template <std::size_t N, typename FunctionPtrType>
    struct FunctionCallResolver : public FunctionInvoker
    {
        using FunctionInfo = helper::MethodTraits<FunctionPtrType>;
        using ParameterType = typename FunctionInfo::ParameterType;

        FunctionCallResolver(FunctionPtrType funcPtr, OpenGLProxy &openGLProxy)
            : mFuncPtr(funcPtr)
            , mOpenGLProxy(openGLProxy)
        {}

        virtual void glCall(const QByteArray &message) override
        {
            auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
            Archive ar = mSerializer.deserialize(message, N, mParams);
            (void)ar;
            mOpenGLProxy.callHelper<N>(mFuncPtr, "", mParams, s);
        }

    private:
        FunctionPtrType mFuncPtr;
        ParameterType mParams;
        Serializer mSerializer;
        OpenGLProxy &mOpenGLProxy;
    };

private slots:
    void onBinaryMessageReceived(const QByteArray &message);

private:
    Serializer mSerializer;
    // akasi TODO client and server must have same interface and be created with factory method
    std::unique_ptr<OpenGLServer> mpOpenGLServer;
    std::unique_ptr<OpenGLClient> mpOpenGLClient;
    ProxyType mProxyType;
    bool mDebug;
    QHash<QString, std::shared_ptr<FunctionInvoker>> mOpenGLFunctionInvokers;
};

#endif // OPENGLPROXY_H
