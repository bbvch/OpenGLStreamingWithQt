/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/22/2015
**   Year:   2015
**************************************************************************/

#include "Serializer.h"
#include "Events.h"

#include <QMouseEvent>

QInputEvent *Serializer::deserializeEvent(const QByteArray &data)
{
    QInputEvent *event = nullptr;
    Archive ar(data, 1, false);
    EventTypes eventType;

    if (mDebug)
        qDebug() << "Deserializing mouse event";

    ar >> eventType;

    if (eventType == EventTypes::eMouseEvent)
    {
        event = createEvent<QMouseEvent,
                            QEvent::Type,
                            QPointF, QPointF, QPointF,
                            Qt::MouseButton,
                            Qt::MouseButtons::Int,
                            Qt::KeyboardModifiers::Int>(ar);
    }
    //TODO akasi: add other events here
    /*else if (eventType == EventTypes::eKeyEvent)
    {


    }*/

    return event;
}

