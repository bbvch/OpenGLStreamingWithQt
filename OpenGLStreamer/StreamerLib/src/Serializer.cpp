/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/22/2015
**   Year:   2015
**************************************************************************/

#include "Serializer.h"
#include "Events.h"

#include <QMouseEvent>

QInputEvent *Serializer::deserialize(const QByteArray &data)
{
    QInputEvent *event = nullptr;
    Archive ar(data, 1, false);
    EventTypes eventType;

    ar >> eventType;

    if (eventType == EventTypes::eMouseEvent)
    {
        if (mDebug)
            qDebug() << "Deserializing mouse event";

        event = deserializeEvent<QMouseEvent,
                                 QEvent::Type,
                                 QPointF, QPointF, QPointF,
                                 Qt::MouseButton,
                                 Qt::MouseButtons,
                                 Qt::KeyboardModifiers>(ar);
    }
    //TODO akasi: add other events here
    /*else if (eventType == EventTypes::eKeyEvent)
    {


    }*/

    return event;
}

