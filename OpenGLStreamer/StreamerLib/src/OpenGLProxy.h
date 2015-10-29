/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLWidget>
#include <QList>

#include <type_traits>
#include <cassert>

#include "Serializer.h"
#include "Helpers.h"

class OpenGLProxy : public QObject
{
    Q_OBJECT

signals:
    void glFunctionSerialized(const QByteArray &message);

public:
    enum CallType
    {
        eServerCall,
        eClientCall,
        eServerAndClientCall
    };

    explicit OpenGLProxy(bool debug = false, QObject *parent = 0)
        : QObject(parent)
        , mDebug(debug)
        , mSerializer(debug)
    {}

    void initialize()
    {
        QOpenGLContext *context = QOpenGLContext::currentContext();
        assert(context != nullptr);
        mOpenGLFuncs = context->versionFunctions<QOpenGLFunctions_2_0>();
        assert(mOpenGLFuncs != nullptr);
    }

    void registerOpenGLWidget(QOpenGLWidget *widget)
    {
        mWidgets.append(widget);
    }

    QOpenGLWidget *findOpenGLWidget(QString name)
    {
        foreach (QOpenGLWidget *pWidget, mWidgets)
        {
            if (name == pWidget->metaObject()->className())
            {
                return pWidget;
            }
        }
        return nullptr;
    }

    template<typename FunctionPtrType, typename... Args>
    typename std::enable_if<std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value, void>::type
    glCall(CallType callType, FunctionPtrType funcPtr, const char *funcName, std::size_t numElemsIfPtr, Args &&...args)
    {
        using FunctionInfo = helper::MethodTraits<decltype(funcPtr)>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        if (callType == eServerCall || callType == eServerAndClientCall)
        {
            callHelper(funcPtr, params, s);
            if (mDebug)
                qDebug() << "OpenGL function" << funcName << "called";
        }
        if (callType == eClientCall || callType == eServerAndClientCall)
        {
            serialize(numElemsIfPtr, funcName, params, s);
        }
    }

    template<typename FunctionPtrType, typename... Args>
    typename std::enable_if<!std::is_void<typename helper::MethodTraits<FunctionPtrType>::ReturnType>::value,
    typename helper::MethodTraits<FunctionPtrType>::ReturnType>::type
    glCall(CallType callType, FunctionPtrType funcPtr, const char *funcName, std::size_t numElemsIfPtr, Args &&...args)
    {
        assert(callType != eClientCall);

        using FunctionInfo = helper::MethodTraits<FunctionPtrType>;
        auto s = typename helper::gens<FunctionInfo::Arity::value>::type();
        typename FunctionInfo::ParameterType params{std::forward<Args>(args)...};

        auto result = callHelper(funcPtr, params, s);
        if (mDebug)
            qDebug() << "OpenGL function" << funcName << "called with return value:" << result;

        if (callType == eServerAndClientCall)
        {
            serialize(numElemsIfPtr, funcName, params, s);
        }

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

        FunctionCallResolver(FunctionPtrType funcPtr, OpenGLProxy &openGLProxy, std::size_t numElemsIfPtr = 0)
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
        std::size_t mNumElemsIfPtr{0};
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
        return (mOpenGLFuncs->*funcPtr)(std::get<S>(params)...);
    }

protected:
    QList<QOpenGLWidget*> mWidgets;
    bool mDebug{false};
    Serializer mSerializer;
    QOpenGLFunctions_2_0 *mOpenGLFuncs;
};

#endif // OPENGLPROXY_H
