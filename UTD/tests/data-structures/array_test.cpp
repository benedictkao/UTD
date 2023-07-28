#include "gtest/gtest.h"

#include "../../src/data-structures/array.h"

TEST(array, int_default_constructor) {
  utd::array<int, 3> arr;
  arr[1] = 5;
  EXPECT_EQ(arr[1], 5);
}

TEST(array, int_initializer_list) {
  utd::array<int, 3> arr = { 1, 2, 3 };

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(array, int_iterator) {
  utd::array<int, 3> arr = { 0 };

  for (int i : arr)
    EXPECT_EQ(i, 0);
}

struct TestObj {
  int  a = 1;
  char b = 'a';
  bool c = false;

  TestObj() = default;
  TestObj(int a, char b, bool c) : a(a), b(b), c(c) {}
};

TEST(array, obj_default_constructor) {
  utd::array<TestObj, 5> arr;
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i].a, 1);
    EXPECT_EQ(arr[i].b, 'a');
    EXPECT_FALSE(arr[i].c);
  }

  TestObj  test            = { 5, 'x', true };
  TestObj* initial_address = &arr[4];
  arr[4]                   = test;
  EXPECT_EQ(arr[4].a, 5);
  EXPECT_EQ(arr[4].b, 'x');
  EXPECT_TRUE(arr[4].c);
  EXPECT_EQ(&arr[4], initial_address);
}

TEST(array, obj_iterator) {
  utd::array<TestObj, 3> arr;
  for (const auto& i : arr) {
    EXPECT_EQ(i.a, 1);
    EXPECT_EQ(i.b, 'a');
    EXPECT_FALSE(i.c);
  }

  for (auto& i : arr)
    i = TestObj(20, '!', true);

  for (const auto& i : arr) {
    EXPECT_EQ(i.a, 20);
    EXPECT_EQ(i.b, '!');
    EXPECT_TRUE(i.c);
  }
}