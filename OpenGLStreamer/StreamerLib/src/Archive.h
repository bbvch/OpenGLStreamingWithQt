/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "Helpers.h"

#include <QByteArray>
#include <QPointF>
#include <QFlag>

#include <algorithm>
#include <type_traits>
#include <cstring>

namespace helper
{
    template <typename T>
    struct SizeOfHelper
    {
        constexpr static std::size_t value = sizeof(T);
    };

    template <>
    struct SizeOfHelper<void>
    {
        constexpr static std::size_t value = 1;
    };
}

class Archive
{
public:
    explicit Archive(const std::size_t &numElemsIfPtr = 0)
        : mNumElemsIfPtr(numElemsIfPtr)
    {}

    explicit Archive(const QByteArray &data, const std::size_t &numElemsIfPtr = 0, bool skipFunctionName = true)
        : mData(data)
        , mNumElemsIfPtr(numElemsIfPtr)
    {
        mDataPointer = data.constData();
        if (skipFunctionName)
        {
            mDataPointer += std::strlen(mDataPointer) + 1;
        }
    }

    Archive(Archive &&) = default;
    Archive(Archive &) = delete;
    Archive &operator= (const Archive &) = delete;
    Archive &operator= (Archive &&) = delete;

    template<typename T>
    typename std::enable_if <std::is_trivial<T>::value && !std::is_pointer<T>::value , Archive &>::type
        operator<<(const T &value)
    {
        mData.append((const char *)&value, sizeof(T));
        return *this;
    }

    template<typename T>
    typename std::enable_if <std::is_trivial<T>::value && std::is_pointer<T>::value , Archive &>::type
        operator<<(const T &value)
    {
        using Type = typename std::remove_cv<
                     typename std::remove_pointer<
                     typename std::decay<T>::type>::type>::type;

        if (std::is_same<char, Type>::value)
        {
            mData.append(reinterpret_cast<const char *>(value));
            mData.append('\0');
        }
        else if(std::is_same<void, Type>::value && mNumElemsIfPtr == 0)
        {
            return operator<<(reinterpret_cast<quintptr>(value));
        }
        else
        {
            auto nBytes = helper::SizeOfHelper<Type>::value*mNumElemsIfPtr;
            auto nBytesOverhead = nBytes/254 + 1;
            quint8 *encodedData = new quint8 [nBytes + nBytesOverhead + 1];
            auto nBytesEncoded = helper::encodeCOB((const quint8 *)value, nBytes, encodedData);
            mData.append(reinterpret_cast<const char *>(encodedData), nBytesEncoded);
            mData.append('\0');

            delete[] encodedData;
        }
        return *this;
    }

    Archive &operator<<(const QPointF &value)
    {
        operator<<(value.x());
        operator<<(value.y());
        return *this;
    }

    template <typename T>
    Archive &operator<<(const QFlags<T> &value)
    {
        return operator<<((typename QFlags<T>::Int)value);
    }

    template<typename T>
    typename std::enable_if <std::is_trivial<T>::value && !std::is_pointer<T>::value , Archive &>::type
        operator>>(T &value)
    {
        std::copy(mDataPointer, mDataPointer + sizeof(T), (char*) &value);
        mDataPointer += sizeof(T);
        return *this;
    }

    template<typename T>
    typename std::enable_if <std::is_trivial<T>::value && std::is_pointer<T>::value , Archive &>::type
        operator>>(T &value)
    {
        using Type = typename std::remove_cv<
                     typename std::remove_pointer<
                     typename std::decay<T>::type>::type>::type;

        if (std::is_same<char, Type>::value)
        {
            value = (Type *)mDataPointer;
            mDataPointer += std::strlen(mDataPointer) + 1;
        }
        else if(std::is_same<void, Type>::value && mNumElemsIfPtr == 0)
        {
            std::copy(mDataPointer, mDataPointer + sizeof(quintptr), (char*) &value);
            mDataPointer += sizeof(quintptr);
        }
        else
        {
            value = (Type *)mDataPointer;
            auto nBytes = std::strlen(mDataPointer);
            helper::decodeCOB((const quint8 *)mDataPointer, nBytes, (quint8 *)mDataPointer);
            mDataPointer += nBytes + 1;
        }
        return *this;
    }

    Archive &operator>>(QPointF &value)
    {
        operator>>(value.rx());
        operator>>(value.ry());
        return *this;
    }

    template <typename T>
    Archive &operator>>(QFlags<T> &value)
    {
        typename QFlags<T>::Int flags;
        operator>>(flags);
        value = QFlags<T>(flags);
        return *this;
    }

    const QByteArray &getData() const
    {
        return mData;
    }

private:
    QByteArray mData;
    std::size_t mNumElemsIfPtr{0};
    const char *mDataPointer{nullptr};
};

#endif // ARCHIVE_H
