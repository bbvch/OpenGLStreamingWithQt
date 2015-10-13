#include <gtest/gtest.h>

#include "Archive.h"

TEST(Archive, CheckInt)
{
    Archive s;

    s << 1;

    const QByteArray &result = s.getData();

    // little-endian of int 1
    const char expected[]{1,0,0,0};

    EXPECT_EQ(sizeof(int), result.length());
    EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));
}

TEST(Archiver, CheckFloat)
{
    Archive s;

    s << 2.f;

    const QByteArray &result = s.getData();

    // IEEE representation of 2.0f
    const char expected[]{0,0,0,0x40};

    EXPECT_EQ(sizeof(float), result.length());
    EXPECT_TRUE(std::equal(expected, expected+4, result.constData()));
}
