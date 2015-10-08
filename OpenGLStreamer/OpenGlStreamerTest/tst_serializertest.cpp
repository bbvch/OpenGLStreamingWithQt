#include <QString>
#include <QtTest>

#include "serializer.h"

class SerializerTest : public QObject
{
    Q_OBJECT

public:
    SerializerTest();

private Q_SLOTS:
    void testMethodIsSerilized();
};

SerializerTest::SerializerTest()
{
}

void SerializerTest::testMethodIsSerilized()
{
    Serializer s;
    int a {1};
    float b {3.};
    Archive archive = s.serialize(Serializer::MessageIds::eGLClear, a, b);

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SerializerTest)

#include "tst_serializertest.moc"
