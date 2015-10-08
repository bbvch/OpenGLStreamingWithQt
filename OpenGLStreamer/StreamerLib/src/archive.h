#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QByteArray>
#include <type_traits>

class Archive
{
public:
    explicit Archive();
    Archive(Archive &&) = default;

    template<
             typename T,
             class = typename std::enable_if<std::is_pod<T>::value>::type
            >
    Archive &operator<< (const T &v)
    {
        mData.append((const char *)&v, sizeof(T));
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
