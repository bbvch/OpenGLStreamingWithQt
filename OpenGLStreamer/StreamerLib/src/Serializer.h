/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Archive.h"
#include "Helpers.h"

#include <QDebug>

#include <tuple>

class QInputEvent;

class Serializer
{
public:
    explicit Serializer(bool debug = false)
        : mDebug(debug)
    {}

    template<typename... Args>
    Archive serialize(const std::size_t &numElemsIfPtr, Args &&...args)
    {
        Archive ar(numElemsIfPtr);
        serializeArguments<0, Args...>(ar, std::move(std::forward_as_tuple(args...)));

        return std::move(ar);
    }

    template<typename... Args>
    Archive deserialize(const QByteArray &data, const std::size_t &numElemsIfPtr, std::tuple<Args ...> &params)
    {
        Archive ar(data, numElemsIfPtr);
        deserializeArguments<0, Args ...>(ar, params);

        return std::move(ar);
    }

    QInputEvent *deserialize(const QByteArray &data);

private:
    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I < sizeof...(Args)), void>::type
       serializeArguments(Archive &ar, std::tuple<Args &...> &&args)
    {
        ar << std::get<I>(args);
        if (mDebug)
            qDebug() << "with parameter" << I << ":" << std::get<I>(args);
        serializeArguments<I + 1, Args...>(ar, std::move(args));
    }

    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I == sizeof...(Args)), void>::type
       serializeArguments(Archive &, std::tuple<Args &...> &&)
    {}

    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I < sizeof...(Args)), void>::type
       deserializeArguments(Archive &ar, std::tuple<Args ...> &args)
    {
        ar >> std::get<I>(args);
        if (mDebug)
            qDebug() << "with parameter" << I << ":" << std::get<I>(args);
        deserializeArguments<I + 1, Args...>(ar, args);
    }

    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I == sizeof...(Args)), void>::type
       deserializeArguments(Archive &, std::tuple<Args ...> &)
    {}

    template <typename T, typename ...Args>
    inline QInputEvent *deserializeEvent(Archive &ar)
    {
        std::tuple<Args ...> params;

        deserializeArguments<0>(ar, params);
        auto s = typename helper::gens<std::tuple_size<decltype(params)>::value>::type();

        return createEvent<T>(params, s);
    }

    template <typename T, typename ...Args, std::size_t ...S>
    inline QInputEvent *createEvent(std::tuple<Args ...> &params, helper::seq<S...>)
    {
        return new T(std::get<S>(params)...);
    }

private:
    bool mDebug{false};
};

#endif // SERIALIZER_H
