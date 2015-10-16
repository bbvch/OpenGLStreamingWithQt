#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QByteArray>
#include <QString>

#include <algorithm>
#include <type_traits>

class Archive
{
public:
    explicit Archive(std::size_t lengthIfPtrPassed = 1)
        : mLengthIfPtrPassed(lengthIfPtrPassed)
    {}

    explicit Archive(const QByteArray &data, std::size_t lengthIfPtrPassed = 1)
        : mData(data)
        , mLengthIfPtrPassed(lengthIfPtrPassed)
    {
        mDataPointer = data.constData();
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
            mData.append(reinterpret_cast<const char *>(value), sizeof(Type)*mLengthIfPtrPassed);
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
            value = (const Type*)mDataPointer;
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
            value = (const Type*)mDataPointer;
            mDataPointer += sizeof(Type)*mLengthIfPtrPassed;
        }
        return *this;
    }


    const QByteArray &getData() const
    {
        return mData;
    }

private:
    QByteArray mData;
    std::size_t mLengthIfPtrPassed;
    const char *mDataPointer{nullptr};
};

#endif // ARCHIVE_H
