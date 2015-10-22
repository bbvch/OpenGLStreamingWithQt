/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/22/2015
**   Year:   2015
**************************************************************************/

#include "Serializer.h"
#include "Events.h"

#include <QMouseEvent>

QEvent *Serializer::deserializeEvent(const QByteArray &data)
{
    QEvent *event = nullptr;
    Archive ar(data, 1, false);
    EventTypes eventType;

    if (mDebug)
        qDebug() << "Deserializing mouse event";

    ar >> eventType;

    if (eventType == EventTypes::eMouseEvent)
    {
        std::tuple<QEvent::Type,
                   QPointF, QPointF, QPointF,
                   Qt::MouseButton, Qt::MouseButtons::Int, Qt::KeyboardModifiers::Int> eventData;
        deserializeArguments<0>(ar, eventData);

        event = new QMouseEvent(std::get<0>(eventData),
                                std::get<1>(eventData),
                                std::get<2>(eventData),
                                std::get<3>(eventData),
                                std::get<4>(eventData),
                                (Qt::MouseButtons)std::get<5>(eventData),
                                (Qt::KeyboardModifiers)std::get<6>(eventData));
    }
    return event;
}

