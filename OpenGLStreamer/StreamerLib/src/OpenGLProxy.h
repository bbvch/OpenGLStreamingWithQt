/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLFunctions_2_0>

#include <type_traits>

#include "Serializer.h"
#include "Helpers.h"

#define STRINGIFY(STR) #STR
#define OPENGL_CALL(NAME, ...) mpOpenGLServer->glCall(&QOpenGLFunctions_2_0::NAME, #NAME, 1, __VA_ARGS__)
#define OPENGL_CALL_V(NAME, VSIZE, DTYPE, ...) mpOpenGLServer->glCall(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, STRINGIFY(NAME##VSIZE##DTYPE##v), VSIZE, __VA_ARGS__)
#define OPENGL_CALL_M(NAME, VSIZE, DTYPE, ...) mpOpenGLServer->glCall(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, STRINGIFY(NAME##VSIZE##DTYPE##v), VSIZE*VSIZE, __VA_ARGS__)

#define CREATE_INVOKER(NAME) {#NAME, std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME)>>(&QOpenGLFunctions_2_0::NAME, *this)}
#define CREATE_INVOKER_V(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v)>>(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, *this, VSIZE)}
#define CREATE_INVOKER_M(NAME, VSIZE, DTYPE) {STRINGIFY(NAME##VSIZE##DTYPE##v), std::make_shared<FunctionCallResolver<decltype(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v)>>(&QOpenGLFunctions_2_0::NAME##VSIZE##DTYPE##v, *this, VSIZE*VSIZE)}

class OpenGLProxy : public QObject, protected QOpenGLFunctions_2_0
{
    Q_OBJECT

signals:
    void glFunctionSerialized(const QByteArray &message);

public:
    explicit OpenGLProxy(bool debug = false, QObject *parent = 0)
        : QObject(parent)
        , mDebug(debug)
        , mSerializer(debug)
    {}

    void initialize()
    {
        initializeOpenGLFunctions();
    }

    template<typename FunctionPtrType, typename... Args>
    typename std::enable_if<std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value, void>::type
    glCall(FunctionPtrType funcPtr, const char *funcName, std::size_t numElemsIfPtr, Args &&...args)
    {
        using FunctionInfo = helper::MethodTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        callHelper(funcPtr, params, s);
        if (mDebug)
            qDebug() << "OpenGL function" << funcName << "called";

        serialize(numElemsIfPtr, funcName, params, s);
    }

    template<typename FunctionPtrType, typename... Args>
    typename std::enable_if<!std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::MethodTraits<FunctionPtrType>::ReturnType>::type
    glCall(FunctionPtrType funcPtr, const char *funcName, std::size_t numElemsIfPtr, Args &&...args)
    {
        using FunctionInfo = helper::MethodTraits<FunctionPtrType>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        auto result = callHelper(funcPtr, params, s);
        if (mDebug)
            qDebug() << "OpenGL function" << funcName << "called with return value:" << result;

        serialize(numElemsIfPtr, funcName, params, s);

        return result;
    }

protected:
    struct FunctionInvoker
    {
        virtual void glCall(const QByteArray &message) = 0;
    };

    template <typename FunctionPtrType>
    struct FunctionCallResolver : public FunctionInvoker
    {
        using FunctionInfo = helper::MethodTraits<FunctionPtrType>;
        using ParameterType = typename FunctionInfo::ParameterType;

        FunctionCallResolver(FunctionPtrType funcPtr, OpenGLProxy &openGLProxy, std::size_t numElemsIfPtr = 1)
            : mFuncPtr(funcPtr)
            , mOpenGLProxy(openGLProxy)
            , mNumElemsIfPtr(numElemsIfPtr)
        {}

        virtual void glCall(const QByteArray &message) override
        {
            auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
            Archive ar = mOpenGLProxy.mSerializer.deserialize(message, mNumElemsIfPtr, mParams);
            mOpenGLProxy.callHelper(mFuncPtr, mParams, s);
            if (mOpenGLProxy.mDebug)
                qDebug() << "OpenGL function" << ar.getData().constData() << "called";
        }

    private:
        FunctionPtrType mFuncPtr;
        ParameterType mParams;
        OpenGLProxy &mOpenGLProxy;
        std::size_t mNumElemsIfPtr{1};
    };

private:
    template<typename ParameterType, std::size_t ...S>
    void serialize(std::size_t numElemsIfPtr, const char *funcName, ParameterType &params, helper::seq<S...>)
    {
        if (mDebug)
            qDebug() << "Serializing OpenGL function:" << funcName;

        emit glFunctionSerialized (mSerializer.serialize(numElemsIfPtr, funcName, std::get<S>(params)...).getData());
    }

    template<typename FunctionPtrType, typename ParameterType, std::size_t ...S>
    typename helper::MethodTraits<FunctionPtrType>::ReturnType
    inline callHelper(FunctionPtrType funcPtr, ParameterType &params, helper::seq<S...>)
    {
        return (this->*funcPtr)(std::get<S>(params)...);
    }

protected:
    bool mDebug{false};
    Serializer mSerializer;
};

#endif // OPENGLPROXY_H
