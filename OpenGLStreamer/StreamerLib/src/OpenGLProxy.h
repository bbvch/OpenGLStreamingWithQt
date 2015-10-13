#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLFunctions>

#include <memory>

#include "OpenGLServer.h"
#include "Serializer.h"

namespace helper
{
    template<typename T>
    struct FunctionTraits;

    template<class Class, typename Return, typename ... Args>
    struct FunctionTraits<Return (Class::*)(Args...)>
    {
       using ClassType = Class;
       using ReturnType = Return;
       using MethodPtrType = Return (Class::*)(Args...);
       using ParameterType = std::tuple<Args...>;
       using Arity = std::tuple_size<ParameterType>;
    };

    template<std::size_t...S> struct seq
    {};

    template<std::size_t N, std::size_t ...S> struct gens : gens < N - 1, N - 1, S... >
    {};

    template<std::size_t ...S> struct gens < 0, S... >
    {
       typedef seq<S...> type;
    };
}

#define OPENGL_CALL(func, ...) mpOpenGLProxy->glCall(&QOpenGLFunctions::func, QString(#func), __VA_ARGS__);

class OpenGLProxy : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLProxy(QObject *parent = 0);

    void initialize();

    template<typename FunctionPtrType, typename... Args >
    void glCall(FunctionPtrType funcPtr, QString funcName, Args &&...args)
    {
        using FunctionInfo = helper::FunctionTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        callHelper(std::move(funcPtr), std::move(funcName), std::move(params), s);
    }
private:
    template<typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    inline void callHelper(FunctionPtrType funcPtr, QString funcName, ParameterType params, helper::seq<S...>)
    {
        (mpOpenGLFunctions->*funcPtr)(std::get<S>(params) ...);
        mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(funcName, std::get<S>(params) ...).getData());
    }

signals:

public slots:
private:
    Serializer mSerializer;
    std::unique_ptr<GlServer> mpOpenGLServer;
    QOpenGLFunctions *mpOpenGLFunctions;
};

#endif // OPENGLPROXY_H
