#include <QString>
#include <QtTest>

#include "serializer.h"

class SerializerTest : public QObject
{
    Q_OBJECT

public:
    SerializerTest();

private Q_SLOTS:
    void testSimpleInt();
    void testSimpleDouble();
};

SerializerTest::SerializerTest()
{
}

void SerializerTest::testSimpleInt()
{
    Archive s;

    s << 1;

    const QByteArray &result = s.getData();

    // little-endian of int 1
    const char expected[]{1,0,0,0};

    QVERIFY2(result.length()==4, "wrong length");
    QVERIFY2(std::equal(expected, expected+4, result.constData()), "wrong content");
}

void SerializerTest::testSimpleDouble()
{
    Archive s;

    s << 2.f;

    const QByteArray &result = s.getData();

    // IEEE representation of 2.0f
    const char expected[]{0,0,0,0x40};

    QVERIFY2(result.length()==4, "wrong length");
    QVERIFY2(std::equal(expected, expected+4, result.constData()), "wrong content");
}

QTEST_APPLESS_MAIN(SerializerTest)

#include "tst_serializertest.moc"
