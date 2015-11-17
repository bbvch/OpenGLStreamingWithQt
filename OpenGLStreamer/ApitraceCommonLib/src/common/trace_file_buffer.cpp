/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   11/12/2015
**   Year:   2015
**************************************************************************/
#include "trace_file.hpp"
#include <cstring>
#include <cassert>

using namespace trace;

class BufferReader : public File {
public:
    explicit BufferReader(File::Mode mode = Mode::ReadWrite);
    virtual ~BufferReader();

    virtual bool supportsOffsets() const;
    virtual File::Offset currentOffset();
protected:
    virtual bool rawOpen(const std::string &filename, File::Mode mode);
    virtual bool rawWrite(const void *buffer, size_t length);
    virtual size_t rawRead(void *buffer, size_t length);
    virtual int rawGetc();
    virtual void rawClose();
    virtual void rawFlush();
    virtual bool rawSkip(size_t length);
    virtual int rawPercentRead();

private:
    const char *m_ptrDataBegin{nullptr};
    const char *m_ptrDataCurrent{nullptr};
    uint64_t m_totalLength{0};
};

BufferReader::BufferReader(File::Mode mode)
    : File(std::string(), mode)
{}

BufferReader::~BufferReader()
{}

bool BufferReader::rawOpen(const std::string&, File::Mode)
{
    return true;
}

bool BufferReader::rawWrite(const void *buffer, size_t length)
{
    assert(buffer && length);
    m_ptrDataBegin = static_cast<const char*>(buffer);
    m_ptrDataCurrent = m_ptrDataBegin;
    m_totalLength = length;

    return true;
}

size_t BufferReader::rawRead(void *buffer, size_t length)
{
    std::ptrdiff_t bytesRead = m_ptrDataCurrent - m_ptrDataBegin;

    if (bytesRead >= m_totalLength) {
        return 0;
    }

    auto bytesLeft = m_totalLength - bytesRead;
    auto bytesCopied = bytesLeft < length ? bytesLeft : length;

    std::memcpy(buffer, m_ptrDataCurrent, bytesCopied);
    m_ptrDataCurrent += bytesCopied;

    return bytesCopied;
}

int BufferReader::rawGetc()
{
    unsigned char c = 0;
    if (rawRead(&c, 1) != 1)
        return -1;
    return c;
}

void BufferReader::rawClose()
{}

void BufferReader::rawFlush()
{}

bool BufferReader::supportsOffsets() const
{
    return false;
}

File::Offset BufferReader::currentOffset()
{
   return File::Offset();
}

bool BufferReader::rawSkip(size_t length)
{
    std::ptrdiff_t bytesRead = m_ptrDataCurrent - m_ptrDataBegin;

    if (bytesRead >= m_totalLength) {
        return false;
    }

    m_ptrDataCurrent += length;

    return true;
}

int BufferReader::rawPercentRead()
{
    return 100;
}


File* File::createBufferReader() {
    return new BufferReader;
}

