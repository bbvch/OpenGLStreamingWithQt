#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QObject>
#include <QByteArray>
#include <type_traits>

class Archive : public QObject
{
    Q_OBJECT
public:
    explicit Archive(QObject *parent = 0);

    template<
             typename T,
             class = typename std::enable_if<std::is_pod<T>::value>::type
            >
    Archive& operator<< (const T& v)
    {
      mData.append((const char*)&v, sizeof(T));
      return *this;
    }

    const QByteArray& getData() const
    {
        return mData;
    }

signals:

public slots:

private:
    QByteArray mData;
};

#endif // ARCHIVE_H
