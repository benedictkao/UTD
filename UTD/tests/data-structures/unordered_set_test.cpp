#include "gtest/gtest.h"

#include "../../src/data-structures/unordered_set.h"

// TODO: add more once iterator is added
TEST(unordered_set, basic_tests) {
  utd::unordered_set<int> s;
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s.max_load_factor(), 1.0);

  s.insert(1);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.bucket_count(), 1);

  s.insert(2);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.bucket_count(), 2);

  s.insert(1);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.bucket_count(), 2);

  s.insert(3);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.bucket_count(), 4);
}