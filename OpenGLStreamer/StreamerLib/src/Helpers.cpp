/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/28/2015
**   Year:   2015
**************************************************************************/

#include "Helpers.h"
#include <cassert>

#define FinishBlock(X) \
   (*code_ptr = (X),  \
   code_ptr = destBuf++,  \
   code = 0x01)

namespace helper
{

static const quint8 ESCAPE_CHAR = 0x00;

quint16 encodeCOB(const quint8 *srcBuf, quint16 srcLen, quint8 *destBuf)
{
    quint16 outputLen = 0;
    const quint8 *end = srcBuf + srcLen;
    quint8 *code_ptr = destBuf++;
    outputLen++;
    quint8 code = 0x01;
    while (srcBuf < end)
    {
        if (*srcBuf == ESCAPE_CHAR)
        {
            FinishBlock(code);
            outputLen++;
        }
        else
        {
            *destBuf++ = *srcBuf;
            outputLen++;
            code++;
            if (code == 0xFF)
            {
                FinishBlock(code);
                outputLen++;
            }
        }
        srcBuf++;
    }
    FinishBlock(code);

    assert(outputLen > srcLen);

    return outputLen;
}

quint16 decodeCOB(const quint8 *srcBuf, quint16 srcLen, quint8 *destBuf)
{
    quint16 outputLen = 0;
    const quint8 *end = srcBuf + srcLen;
    while (srcBuf < end)
    {
        quint8 code = *srcBuf++;
        for (int i = 1; i < code; i++)
        {
            *destBuf++ = *srcBuf++;
            outputLen++;
        }
        if (code < 0xFF)
        {
            *destBuf++ = ESCAPE_CHAR;
            outputLen++;
        }
    }
    outputLen--;

    assert(outputLen < srcLen);

    return outputLen;
}
}
