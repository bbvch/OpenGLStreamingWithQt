#include <QString>
#include <QtTest>

#include "serializer.h"

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
    Serializer s;
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SerializerTest)

#include "tst_serializertest.moc"
