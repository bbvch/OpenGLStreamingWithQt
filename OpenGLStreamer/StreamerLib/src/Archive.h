#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QByteArray>
#include <QString>
#include <type_traits>

class Archive
{
public:
    explicit Archive() = default;
    Archive(Archive &&) = default;
    Archive(Archive &) = delete;
    Archive &operator= (const Archive &) = delete;
    Archive &operator= (Archive &&) = delete;

    template<typename T>
    typename std::enable_if <std::is_trivial<T>::value, Archive &>::type
        operator<<(const T &value)
    {
        mData.append((const char *)&value, sizeof(T));
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
};

#endif // ARCHIVE_H
