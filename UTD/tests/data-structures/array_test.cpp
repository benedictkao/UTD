#include "gtest/gtest.h"

#include "../../src/data-structures/array.h"

TEST(array, int_array) {
  //TODO: add array constructor so that array can be constructed like:
  //utd::array<int, 3> a1 = { 1, 2, 3 };

  utd::array<int, 3> arr;

  // TODO: add iterator in array so that can run for each loop
  //for (int i = 0; i < 3; i++) {
  //  EXPECT_EQ(arr[i], 0);
  //}

  arr[1] = 5;
  EXPECT_EQ(arr[1], 5);
}

struct TestObj {
  int  a = 1;
  char b = 'a';
  bool c = false;
};

TEST(array, obj_array) {
  utd::array<TestObj, 5> arr;
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i].a, 1);
    EXPECT_EQ(arr[i].b, 'a');
    EXPECT_FALSE(arr[i].c);
  }

  TestObj test = { 5, 'x', true };
  TestObj* initial_address = &arr[4];
  arr[4]                   = test;
  EXPECT_EQ(arr[4].a, 5);
  EXPECT_EQ(arr[4].b, 'x');
  EXPECT_TRUE(arr[4].c);
  EXPECT_EQ(&arr[4], initial_address);
}