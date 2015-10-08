#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>

class Serializer : public QObject
{
    Q_OBJECT
public:

    // TODO akasi: move it from here
    enum class MessageIds
    {
        eGLClear,
        eGLClearColor
    };

    explicit Serializer(QObject *parent = 0);

    template<typename ... Args>
    void serialize(MessageIds id, Args... args)
    {
        QByteArray data;
        data += id;

    }

signals:

public slots:

private:
};

#endif // SERIALIZER_H
