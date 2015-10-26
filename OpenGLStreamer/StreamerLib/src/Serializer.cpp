/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/22/2015
**   Year:   2015
**************************************************************************/

#include "Serializer.h"
#include "Events.h"

#include <QMouseEvent>
#include <QPaintEvent>

QEvent *Serializer::deserialize(Archive &ar)
{
    QEvent *event = nullptr;
    EventTypes eventType;

    ar >> eventType;

    if (eventType == EventTypes::eMouseEvent)
    {
        if (mDebug)
            qDebug() << "MouseEvent was received";
        event = deserializeEvent<QMouseEvent,
                                 QEvent::Type,
                                 QPointF, QPointF, QPointF,
                                 Qt::MouseButton,
                                 Qt::MouseButtons,
                                 Qt::KeyboardModifiers>(ar);
    }
    else if (eventType == EventTypes::eUpdateEvent)
    {
        if (mDebug)
            qDebug() << "UpdateEvent was received";

        event = new QPaintEvent(QRegion());
    }
    //TODO akasi: add other events here
    /*else if (eventType == EventTypes::eKeyEvent)
    {


    }*/

    return event;
}

