/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/28/2015
**   Year:   2015
**************************************************************************/
#include <gtest/gtest.h>

#include "Helpers.h"

TEST(Helpers, EncodeString)
{
   const char str[] = "sample_string_01230*";
   char strEncoded[sizeof(str) + 1 + 1];
   char strDecoded[sizeof(str)];

   auto nByteEncoded = helper::encodeCOB((const quint8 *)&str[0], sizeof(str), (quint8 *)&strEncoded[0]);
   auto nByteDecoded = helper::decodeCOB((const quint8 *)&strEncoded[0], nByteEncoded, (quint8 *)&strDecoded[0]);

   EXPECT_EQ(sizeof(str) + 1, nByteEncoded);
   EXPECT_EQ(sizeof(str), nByteDecoded);
   EXPECT_STREQ(str, strDecoded);
}

TEST(Helpers, EncodeByteArray)
{
   const quint8 data[] = {1,2,3,4,0,0,0,1,23,4,5,7,8,0,0,0,0,0,0,234};
   quint8 dataEncoded[sizeof(data) + 1 + 1];
   quint8 dataDecoded[sizeof(data)];

   auto nByteEncoded = helper::encodeCOB((const quint8 *)&data[0], sizeof(data), (quint8 *)&dataEncoded[0]);
   auto nByteDecoded = helper::decodeCOB((const quint8 *)&dataEncoded[0], nByteEncoded, (quint8 *)&dataDecoded[0]);

   EXPECT_EQ(sizeof(data) + 1, nByteEncoded);
   EXPECT_EQ(sizeof(data), nByteDecoded);
   EXPECT_TRUE(std::equal(data, data + sizeof(data), dataDecoded));
}

TEST(Helpers, DecodeByteArrayIntoSameLocation)
{
    const quint8 data[] = {1,2,3,4,0,0,0,1,23,4,5,7,8,0,0,0,0,0,0,234};
    quint8 dataEncoded[sizeof(data) + 1 + 1];

    auto nByteEncoded = helper::encodeCOB((const quint8 *)&data[0], sizeof(data), (quint8 *)&dataEncoded[0]);
    auto nByteDecoded = helper::decodeCOB((const quint8 *)&dataEncoded[0], nByteEncoded, (quint8 *)&dataEncoded[0]);

    EXPECT_EQ(sizeof(data) + 1, nByteEncoded);
    EXPECT_EQ(sizeof(data), nByteDecoded);
    EXPECT_TRUE(std::equal(data, data + sizeof(data), dataEncoded));
}
