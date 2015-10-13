#ifndef CHANNEL_H
#define CHANNEL_H

#include <QByteArray>

class ChannelInterface
{
public:
    virtual ~ChannelInterface() = default;

    virtual void send(QByteArray data) = 0;

    virtual QByteArray receive() = 0;
};

#endif // CHANNEL_H
