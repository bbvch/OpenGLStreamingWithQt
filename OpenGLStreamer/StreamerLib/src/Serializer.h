#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Archive.h"

#include <QObject>

#include <tuple>

class Serializer : public QObject
{
    Q_OBJECT
public:
    explicit Serializer(QObject *parent = 0);

    template<typename... Args>
    Archive serialize(std::size_t lengthIfPtrPassed, Args &&...args)
    {
        Archive ar(lengthIfPtrPassed);
        serializeArguments<0, Args...>(ar, std::move(std::forward_as_tuple(args...)));

        return std::move(ar);
    }

    template<typename... Args>
    Archive deserialize(const QByteArray &data, std::size_t lengthIfPtrPassed, std::tuple<Args...> &params)
    {
        Archive ar(data, lengthIfPtrPassed);
        deserializeArguments<0, Args...>(ar, params);

        return std::move(ar);
    }

signals:

public slots:

private:
    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I < sizeof...(Args)), void>::type
       serializeArguments(Archive &ar, std::tuple<Args &...> &&args)
    {
        ar << std::get<I>(args);
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
        deserializeArguments<I + 1, Args...>(ar, args);
    }

    template <std::size_t I, typename... Args>
    inline typename std::enable_if<(I == sizeof...(Args)), void>::type
       deserializeArguments(Archive &, std::tuple<Args ...> &)
    {}

};

#endif // SERIALIZER_H
