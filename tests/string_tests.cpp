#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringTest, Constructor)
{
  {
    String str;

    EXPECT_TRUE(str.empty());
    EXPECT_EQ(0, str.length());
    EXPECT_EQ(0, str.size());
    EXPECT_EQ(0, str.max_size());
    EXPECT_EQ(nullptr, str.data());
  }
  {
    char data[10];
    std::memset(data, 'a', 10);
    String str(10, 'a');

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(10, str.length());
    EXPECT_EQ(10, str.size());
    EXPECT_EQ(10, str.max_size());
    EXPECT_EQ(0, std::memcmp(data, str.data(), 10));
  }
  {
    char data[10];
    std::memset(data, 'a', 10);
    String str(data, 10);

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(10, str.length());
    EXPECT_EQ(10, str.size());
    EXPECT_EQ(10, str.max_size());
    EXPECT_EQ(0, std::memcmp(data, str.data(), 10));
  }
  {
    char data[]          = "abcdefghijklmnopqrstuvwxyz";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str(data);

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(dataSize, str.length());
    EXPECT_EQ(dataSize, str.size());
    EXPECT_EQ(dataSize, str.max_size());
    EXPECT_EQ(0, std::memcmp(data, str.data(), str.size()));
  }
  {
    char data[]          = "abcdefghijklmnopqrstuvwxyz";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1(data);
    String str2(str1);

    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(dataSize, str1.length());
    EXPECT_EQ(dataSize, str1.size());
    EXPECT_EQ(dataSize, str1.max_size());
    EXPECT_EQ(0, std::memcmp(data, str1.data(), str1.size()));

    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(dataSize, str2.length());
    EXPECT_EQ(dataSize, str2.size());
    EXPECT_EQ(dataSize, str2.max_size());
    EXPECT_EQ(0, std::memcmp(data, str2.data(),str2.size()));
  }
  {
    char data[]          = "abcdefghijklmnopqrstuvwxyz";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1(data);
    String str2(std::move(str1));
    
    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(0, str1.length());
    EXPECT_EQ(0, str1.size());
    EXPECT_EQ(0, str1.max_size());
    EXPECT_EQ(nullptr, str1.data());

    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(dataSize, str2.length());
    EXPECT_EQ(dataSize, str2.size());
    EXPECT_EQ(dataSize, str2.max_size());
    EXPECT_EQ(0, std::memcmp(data, str2.data(), str2.size()));
  }
  {
    char data[] = "abcdef";
    String str = {'a', 'b', 'c', 'd', 'e', 'f'};

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(6, str.length());
    EXPECT_EQ(6, str.size());
    EXPECT_EQ(6, str.max_size());
    EXPECT_EQ(0, std::memcmp(data, str.data(), 6));
  }
}

TEST(StringTest, Assignment)
{
  {
    char data[]          = "abcdefg";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str(data);

    str = str;

    EXPECT_FALSE(str.empty());
    EXPECT_EQ(dataSize, str.length());
    EXPECT_EQ(dataSize, str.size());
    EXPECT_EQ(dataSize, str.max_size());
    EXPECT_EQ(0, std::memcmp(data, str.data(), str.size()));
  }
  {
    char data[]          = "abcdef";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1;
    String str2(data);

    str1 = str2;

    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(dataSize, str1.length());
    EXPECT_EQ(dataSize, str1.size());
    EXPECT_EQ(dataSize, str1.max_size());

    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(dataSize, str2.length());
    EXPECT_EQ(dataSize, str2.size());
    EXPECT_EQ(dataSize, str2.max_size());
  }
  {
    char data[] = "abcdef";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1(data);
    String str2;

    str1 = str2;

    EXPECT_TRUE(str1.empty());
    EXPECT_EQ(0, str1.length());
    EXPECT_EQ(0, str1.size());
    EXPECT_EQ(dataSize, str1.max_size());

    EXPECT_TRUE(str2.empty());
    EXPECT_EQ(0, str2.length());
    EXPECT_EQ(0, str2.size());
    EXPECT_EQ(0, str2.max_size());
  }
  {
    char data[] = "abcdef";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1;
    String str2(data);

    str1 = std::move(str2);

    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(dataSize, str1.length());
    EXPECT_EQ(dataSize, str1.size());
    EXPECT_EQ(dataSize, str1.max_size());

    EXPECT_TRUE(str2.empty());
    EXPECT_EQ(0, str2.length());
    EXPECT_EQ(0, str2.size());
    EXPECT_EQ(0, str2.max_size());
  }
}

TEST(StringTest, Addition)
{
  {
    char data[] = "abcdef";
    std::size_t dataSize = sizeof(data)/sizeof(char) - 1;
    String str1(data);
    String str2 = str1 + str1;
    
    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(dataSize, str1.length());
    EXPECT_EQ(dataSize, str1.size());
    EXPECT_EQ(dataSize, str1.max_size());
    EXPECT_EQ(0, std::memcmp(data, str1.data(), dataSize));

    EXPECT_FALSE(str2.empty());
    EXPECT_EQ(2 * dataSize, str2.length());
    EXPECT_EQ(2 * dataSize, str2.size());
    EXPECT_EQ(2 * dataSize, str2.max_size());
    EXPECT_EQ(0, std::memcmp(data, str2.data(), dataSize));
    EXPECT_EQ(0, std::memcmp(data, str2.data()+dataSize, dataSize));
  }
}

TEST(StringTest, AdditionAssignment)
{
  {
    char data[] = "abdef";
    std::size_t dataSize = sizeof(data)/sizeof(char)-1;
    String str1(data);

    str1 += str1;

    EXPECT_FALSE(str1.empty());
    EXPECT_EQ(2 * dataSize, str1.length());
    EXPECT_EQ(2 * dataSize, str1.size());
    EXPECT_EQ(2 * dataSize, str1.max_size());

    EXPECT_EQ(0, std::memcmp(data, str1.data(), dataSize));
    EXPECT_EQ(0, std::memcmp(data, str1.data()+dataSize, dataSize));
  }
}

TEST(StringTest, Equality)
{
  {
    char data[] = "abdef";
    std::size_t dataSize = sizeof(data)/sizeof(char)-1;
    String str(data);

    EXPECT_EQ(str, str);
  }
  {
    char data[] = "abdef";
    std::size_t dataSize = sizeof(data)/sizeof(char)-1;
    String str1(data);
    String str2(data);

    EXPECT_EQ(str1, str2);
  }
}