#ifndef OPENGLPROXY_H
#define OPENGLPROXY_H

#include <QObject>
#include <QOpenGLFunctions>

#include <memory>

#include "OpenGLServer.h"
#include "Serializer.h"

template<typename T>
struct method_type_traits;

template<class Class, typename Return, typename ... Args>
struct method_type_traits<Return (Class::*)(Args...)>
{
   using ClassType = Class; ///< Class of method
   using ReturnType = Return; ///< Return type of method
   using MethodPtrType = Return (Class::*)(Args...); ///< Type of method pointer
   using ParameterType = std::tuple<Args...>; ///< Tuple type containing the method arguments
   using Arity = std::tuple_size<ParameterType>; ///< Number of method argum
};

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
        //using FunctionInfo = method_type_traits<decltype(funcPtr)>;
        (mpOpenGLFunctions->*funcPtr)(std::forward<Args>(args)...);
        mpOpenGLServer->sendBinaryMessage(mSerializer.serialize(funcName, std::forward<Args>(args)...).getData());
    }

signals:

public slots:
private:
    Serializer mSerializer;
    std::unique_ptr<GlServer> mpOpenGLServer;
    QOpenGLFunctions *mpOpenGLFunctions;
};

#endif // OPENGLPROXY_H
