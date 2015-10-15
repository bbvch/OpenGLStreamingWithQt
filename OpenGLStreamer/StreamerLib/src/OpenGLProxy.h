#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLFunctions>

#include <memory>
#include <type_traits>

#include "OpenGLServer.h"
#include "Serializer.h"

#define OPENGL_CALL(_func, ...) mpOpenGLProxy->glCall<1>(&QOpenGLFunctions::_func, QString(#_func), __VA_ARGS__)
#define OPENGL_CALL_V(_func, _vsize, _type, ...) mpOpenGLProxy->glCall<_vsize>(&QOpenGLFunctions::_func##_vsize##_type##v, QString(#_func), __VA_ARGS__)

namespace helper
{
    template<typename T>
    struct FunctionTraits;

    template<class Class, typename Return, typename ... Args>
    struct FunctionTraits<Return (Class::*)(Args...)>
    {
       using ClassType = Class;
       using ReturnType = Return;
       using FunctionPtrType = Return (Class::*)(Args...);
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

class OpenGLProxy : public QObject
{
    Q_OBJECT
public:
    explicit OpenGLProxy(QObject *parent = 0);

    void initialize();

    template<std::size_t N, typename FunctionPtrType, typename... Args>
    typename std::enable_if<std::is_void<typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::value, void>::type
    glCall(FunctionPtrType funcPtr, QString funcName, Args &&...args)
    {
        using FunctionInfo = helper::FunctionTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        callHelper<N>(std::move(funcPtr), std::move(funcName), std::move(params), s);
    }

    template<std::size_t N, typename FunctionPtrType, typename... Args>
    typename std::enable_if<!std::is_void<typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::type
    glCall(FunctionPtrType funcPtr, QString funcName, Args &&...args)
    {
        using FunctionInfo = helper::FunctionTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        return callHelper<N>(std::move(funcPtr), std::move(funcName), std::move(params), s);
    }

private:
    template<std::size_t N, typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    typename std::enable_if<std::is_void<typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::value, void>::type
    callHelper(FunctionPtrType funcPtr, QString funcName, ParameterType params, helper::seq<S...>)
    {
        (mpOpenGLFunctions->*funcPtr)(std::get<S>(params)...);
        mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(N, funcName, std::get<S>(params)...).getData());
    }

    template<std::size_t N, typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    typename std::enable_if<!std::is_void<typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::FunctionTraits<FunctionPtrType>::ReturnType>::type
    callHelper(FunctionPtrType funcPtr, QString funcName, ParameterType params, helper::seq<S...>)
    {
        auto result = (mpOpenGLFunctions->*funcPtr)(std::get<S>(params)...);
        mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(N, funcName, std::get<S>(params)...).getData());

        return result;
    }

signals:

public slots:
private:
    Serializer mSerializer;
    std::unique_ptr<OpenGLServer> mpOpenGLServer;
    QOpenGLFunctions *mpOpenGLFunctions;
};

#endif // OPENGLPROXY_H
