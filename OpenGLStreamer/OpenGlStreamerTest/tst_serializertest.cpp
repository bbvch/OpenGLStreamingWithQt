#include <QString>
#include <QtTest>

#include "archive.h"

class SerializerTest : public QObject
{
    Q_OBJECT

public:
    SerializerTest();

private Q_SLOTS:
    void testCase1();
};

SerializerTest::SerializerTest()
{
}

void SerializerTest::testCase1()
{
    Archive s;

    int i = 0;
    s << 1 << i << 1.5;

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SerializerTest)

#include "tst_serializertest.moc"
