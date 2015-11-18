#include "trace_serializer.h"

#include <QDebug>
#include <QFile>

TraceSerializer::TraceSerializer(QObject *parent)
    : QObject(parent)
{
    open(nullptr);
}

TraceSerializer::~TraceSerializer()
{
    close();
}

trace::Call *TraceSerializer::scanSerializedCall(const QByteArray &callData)
{
    if (callData.isEmpty()) {
        return nullptr;
    }

    setData(callData, callData.length());
    trace::Call *call = scan_call();
    if (call && (m_numInitFrames < m_totalInitFrames)) {
        ++m_numInitCalls;
        m_initFrame.append(callData);
        if (call->flags & trace::CALL_FLAG_END_FRAME) {
            ++m_numInitFrames;
            if (m_numInitFrames == m_totalInitFrames) {
                emit initFrameCreated(m_initFrame);
            }
        }
    }
    return call;
}

void TraceSerializer::resetSignatures()
{
    trace::Parser::resetSignatures();
}
