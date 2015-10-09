#include "gtest/gtest.h"

#include "archive.h"

TEST(Archiver, check__single_integer) {

    Archive s;

    s << 1;

    const QByteArray &result = s.getData();

    // little-endian of int 1
    const char expected[]{1,0,0,0};

    EXPECT_EQ(4, result.length());
    EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));

}


TEST(Archiver, check__single_float) {

    Archive s;

    s << 2.f;

    const QByteArray &result = s.getData();

    // IEEE representation of 2.0f
    const char expected[]{0,0,0,0x40};

    EXPECT_EQ(4, result.length());
    EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));

}


