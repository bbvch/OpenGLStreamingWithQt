#pragma once

#include "trace_file.hpp"
#include "trace_parser.hpp"

#include <QObject>
#include <QByteArray>

class TraceSerializer : public QObject
                      , public trace::Parser
{
    Q_OBJECT
public:
    TraceSerializer(QObject *parent=0);
    ~TraceSerializer();

    const QByteArray &getInitFrame()
    {
        return m_initFrame;
    }

    void resetSignatures();

    trace::Call *scanSerializedCall(const QByteArray &callData);

signals:
    void initFrameCreated(const QByteArray &callData);

private:
    QByteArray m_initFrame;
    quint16 m_totalInitFrames{1};
    quint16 m_numInitFrames{0};
    quint16 m_numInitCalls{0};
};
