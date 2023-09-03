#include "gtest/gtest.h"

#include "../../src/data-structures/unordered_set_m.h"

// TODO: add more once iterator is added
TEST(unordered_set_m, basic_tests) {
  utd::unordered_set_m<int> s;
  ASSERT_EQ(s.size(), 0);
  ASSERT_EQ(s.max_load_factor(), 1.0);
};

TEST(unordered_set_m, basic_tests_2) {
  utd::unordered_set_m<int> s;
  s.insert(1);
  s.insert(1);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.bucket_count(), 2);

  const utd::node_m<int>* head = (s.begin());
  while (head) {
    std::cout << head->value << std::endl;
    head = head->next;
  }
};

TEST(unordered_set_m, basic_tests_3) {
  utd::unordered_set_m<int> s;

  s.insert(31);
  s.insert(43);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.bucket_count(), 2);

  s.insert(99);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.bucket_count(), 3);

  s.insert(1);
  ASSERT_EQ(s.size(), 4);
  ASSERT_EQ(s.bucket_count(), 4);

  s.insert(3);
  ASSERT_EQ(s.size(), 5);
  ASSERT_EQ(s.bucket_count(), 5);


  const utd::node_m<int>* head = (s.begin());
  while (head) {
    std::cout << head->value << std::endl;
    head = head->next;
  }
};

TEST(unordered_set_m, basic_tests_4) {
  utd::unordered_set_m<int> s;
  s.max_load_factor(10.0);

  s.insert(31);
  s.insert(43);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.bucket_count(), 1);

  s.insert(99);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.bucket_count(), 1);

  s.insert(1);
  ASSERT_EQ(s.size(), 4);
  ASSERT_EQ(s.bucket_count(), 1);

  s.insert(3);
  ASSERT_EQ(s.size(), 5);
  ASSERT_EQ(s.bucket_count(), 1);

  const utd::node_m<int>* head = (s.begin());
  while (head) {
    std::cout << head->value << std::endl;
    head = head->next;
  }
};