#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QByteArray>
#include <QString>
#include <type_traits>

class Archive
{
public:
    explicit Archive(std::size_t lengthIfPtrPassed = 1)
        : mLengthIfPtrPassed(lengthIfPtrPassed)
    {}

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

    Archive &operator<<(const QString &value)
    {
        mData.append(value);
        return *this;
    }


    const QByteArray &getData() const
    {
        return mData;
    }

private:
    QByteArray mData;
    std::size_t mLengthIfPtrPassed;
};

#endif // ARCHIVE_H
