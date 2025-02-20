#include <gtest/gtest.h>

#include "allocator.hpp"

TEST(AllocatorTest, SingleAllocation)
{
  Allocator<char> alloc;
  char * str = alloc.allocate(10);
  ASSERT_NE(nullptr, str);
  alloc.deallocate(str, 10);
}

