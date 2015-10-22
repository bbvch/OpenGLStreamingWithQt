/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/17/2015
**   Year:   2015
**************************************************************************/

#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QByteArray>

#include <algorithm>
#include <type_traits>

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
        constexpr static std::size_t value = 0;
    };
}

class Archive
{
public:
    explicit Archive(const std::size_t &numElemsIfPtr = 1)
        : mNumElemsIfPtr(numElemsIfPtr)
    {}

    explicit Archive(const QByteArray &data, const std::size_t &numElemsIfPtr = 1)
        : mData(data)
        , mNumElemsIfPtr(numElemsIfPtr)
    {
        mDataPointer = data.constData();
        while(*(mDataPointer++) != '\0')
        {}
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
        else if(std::is_same<void, Type>::value)
        {
            quintptr ptrValue = reinterpret_cast<quintptr>(value);
            return operator<<(ptrValue);
        }
        else
        {
            mData.append(reinterpret_cast<const char *>(value), helper::SizeOfHelper<Type>::value*mNumElemsIfPtr);
        }
        return *this;
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
            while(*(mDataPointer++) != '\0')
            {}
        }
        else if(std::is_same<void, Type>::value)
        {
            std::copy(mDataPointer, mDataPointer + sizeof(quintptr), (char*) &value);
            mDataPointer += sizeof(quintptr);
        }
        else
        {
            value = (Type *)mDataPointer;
            mDataPointer += helper::SizeOfHelper<Type>::value*mNumElemsIfPtr;
        }
        return *this;
    }


    const QByteArray &getData() const
    {
        return mData;
    }

private:
    QByteArray mData;
    std::size_t mNumElemsIfPtr;
    const char *mDataPointer{nullptr};
};

#endif // ARCHIVE_H
