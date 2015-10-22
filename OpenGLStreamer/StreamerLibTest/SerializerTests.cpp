#include <gtest/gtest.h>

#include "Serializer.h"

TEST(Serializer, IntIsSerialized)
{
   Serializer s;

   int i = 123456;

   Archive a = s.serialize(1, i);

   const QByteArray &result = a.getData();

   // little-endian of int 123456
   const char expected[]{0x40,0xE2,0x01,0x0};

   EXPECT_EQ(sizeof(int), result.length());
   EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));
}

TEST(Serializer, FloatIsSerialized)
{
    Serializer s;

    float f = 123456.1234;

    Archive a = s.serialize(1, f);

    const QByteArray &result = a.getData();

    // little-endian of float 123456.1234
    const char expected[]{0x10,0x20,0xF1,0x47};

    EXPECT_EQ(sizeof(float), result.length());
    EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));
}

TEST(Serializer, DoubleIsSerialized)
{
    Serializer s;

    double d = 14.5e-14;

    Archive a = s.serialize(1, d);

    const QByteArray &result = a.getData();

    // little-endian of double 14.5e-14
    const char expected[]{0x84,0x0F,0x02,0xF2,0x2C,0x68,0x44,0x3d};

    EXPECT_EQ(sizeof(double), result.length());
    EXPECT_TRUE(std::equal(expected, expected+8, result.constData()));
}

TEST(Serializer, BoolIsSerialized)
{
    Serializer s;

    bool b = true;

    Archive a = s.serialize(1, b);

    const QByteArray &result = a.getData();

    // little-endian of bool
    const char expected[]{1};

    EXPECT_EQ(sizeof(bool), result.length());
    EXPECT_TRUE(std::equal(expected, expected+1, result.constData()));
}

TEST(Serializer, PtrCharIsSerialized)
{
    Serializer s;

    Archive a = s.serialize(1, "some_string");

    const QByteArray &data = a.getData();

    QString expected("some_string");
    QString result(data.constBegin());

    EXPECT_EQ(12, data.length());
    EXPECT_EQ(expected, result);
}

TEST(Serializer, PtrVoidIsSerialized)
{
    Serializer s;

    int d = 15;
    void *ptr = &d;

    long long address = (long long)ptr;

    Archive a = s.serialize(1, ptr);

    const QByteArray &data = a.getData();

    std::vector<char> expected((const char*)&address, (const char*)&address + sizeof(ptr));
    std::vector<char> result(data.constBegin(), data.constEnd());

    EXPECT_EQ(sizeof(int*), data.length());
    EXPECT_EQ(expected, result);
}

TEST(Serializer, PtrFloatIsSerialized)
{
    Serializer s;

    std::array<float, 4> f{1.6, 1.7, 1e-4, 456.9};
    float *ptr = &f[0];

    Archive a = s.serialize(f.size(), ptr);

    const QByteArray &data = a.getData();

    std::vector<char> expected((const char*)&f[0], (const char*)&f[0] + sizeof(f));
    std::vector<char> result(data.constBegin(), data.constEnd());

    EXPECT_EQ(sizeof(f), data.length());
    EXPECT_EQ(expected, result);
}

TEST(Serializer, RValuesAreSerialized)
{
    Serializer s;

    Archive a = s.serialize(1, 1, 1.3);

    auto i = 1;
    auto f = 1.3;

    const QByteArray &data = a.getData();

    std::vector<char> expected;
    expected.insert(expected.end(), (const char*)&i, (const char*)&i + sizeof(i));
    expected.insert(expected.end(), (const char*)&f, (const char*)&f + sizeof(f));

    std::vector<char> result(data.constBegin(), data.constEnd());

    EXPECT_EQ(sizeof(i) + sizeof(f), data.length());
    EXPECT_EQ(expected, result);
}
