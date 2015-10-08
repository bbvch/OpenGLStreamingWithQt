#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>

class Serializer : public QObject
{
    Q_OBJECT
public:
    explicit Serializer(QObject *parent = 0);

signals:

public slots:
};

#endif // SERIALIZER_H
