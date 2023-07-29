#include "gtest/gtest.h"

#include "../../src/data-structures/vector.h"

using utd::vector;

TEST(vector, empty_constructor) {
  // Empty constructor
  vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.begin(), v.end());
}

TEST(vector, size_constructor) {
  // size constructor
  vector<int> v_size(10);
  EXPECT_EQ(v_size.size(), 10);
  EXPECT_NE(v_size.begin(), v_size.end());
}

TEST(vector, size_val_constructor) {
  // size + val constructor
  vector<int> v_size_val(11, 1);
  EXPECT_EQ(v_size_val.size(), 11);
  EXPECT_NE(v_size_val.begin(), v_size_val.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_size_val[i], 1);
  }
  EXPECT_EQ(*v_size_val.begin(), *v_size_val.end());
}

TEST(vector, copy_constructor) {
  // Copy constructor
  vector<int> v_size_val(11, 1);
  vector<int> v_copy(v_size_val);
  EXPECT_EQ(v_copy.size(), 11);
  EXPECT_NE(v_copy.begin(), v_copy.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_copy[i], 1);
  }
}

TEST(vector, move_constructor) {
  // Move constructor
  vector<int> v_source(11, 100);
  vector<int> v_move(std::move(v_source));
  EXPECT_EQ(v_source.size(), 0);
  EXPECT_EQ(v_move.size(), 11);
  EXPECT_NE(v_move.begin(), v_move.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_move[i], 100);
  }
  EXPECT_EQ(*v_move.begin(), *v_move.end());
}

class VectorMethodsTest : public ::testing::Test {
protected:
  void SetUp() override {
    for (int i = 0; i < v10_size; i++)
      v10.push_back(i);

    for (int i = 0; i < v100_size; i++)
      v100.push_back(i);
  }

  vector<int> v;
  vector<int> v10;
  vector<int> v100;

  int v10_size  = 10;
  int v100_size = 100;
};

TEST_F(VectorMethodsTest, IsEmptyInitially) {
  EXPECT_EQ(v.size(), 0);
}

TEST_F(VectorMethodsTest, SameIteratorInitially) {
  EXPECT_EQ(v.begin(), v.end());
}

TEST_F(VectorMethodsTest, PushBack100) {
  size_t v_size = 1000;
  for (int i = 0; i < v_size; i++)
    v.push_back(i);
  EXPECT_EQ(v.size(), v_size);
}

TEST_F(VectorMethodsTest, AtGetter) {
  for (int i = 0; i < v100_size; i++)
    EXPECT_EQ(v100.at(i), i);
}

TEST_F(VectorMethodsTest, IndexerGetter) {
  for (int i = 0; i < v100_size; i++)
    EXPECT_EQ(v100[i], i);
}

TEST_F(VectorMethodsTest, IteratorGetter) {
  for (int i = 0; i < v100_size; i++)
    EXPECT_EQ(*(v100.begin() + i), i);
}

TEST_F(VectorMethodsTest, PopBack20Times) {
  int pop_back_times  = 20;
  int expected_v_size = v100_size - pop_back_times;

  while (pop_back_times-- > 0)
    v100.pop_back();

  EXPECT_EQ(v100.size(), expected_v_size);

  for (int i = 0; i < v.size(); i++)
    EXPECT_EQ(v.at(i), i);
}

TEST_F(VectorMethodsTest, Resize10) {
  int new_v_size = 10;
  v100.resize(new_v_size);
  EXPECT_EQ(v100.size(), new_v_size);
  for (int i = 0; i < new_v_size; i++)
    EXPECT_EQ(v100.at(i), i);
}

TEST_F(VectorMethodsTest, Resize20) {
  int new_v_size = 20;
  v10.resize(new_v_size);
  EXPECT_EQ(v10.size(), new_v_size);
  for (int i = 0; i < new_v_size; i++)
    if (i < 10)
      EXPECT_EQ(v10.at(i), i);
    else
      EXPECT_EQ(v10.at(i), 0);
}

TEST_F(VectorMethodsTest, Resize30WithValue) {
  int new_v_size = 30;
  int new_v_val  = 7;
  v10.resize(new_v_size, new_v_val);
  EXPECT_EQ(v10.size(), new_v_size);
  for (int i = 0; i < new_v_size; i++)
    if (i < 10)
      EXPECT_EQ(v10.at(i), i);
    else
      EXPECT_EQ(v10.at(i), new_v_val);
}


TEST(vector, exception_IdxOutOfRange) {
  EXPECT_THROW(
    {
      vector<int> v(10, 10);
      v[10];
    },
    vector<int>::IdxOutOfRange);

  EXPECT_THROW(
    {
      vector<int> v(10, 10);
      v.at(10);
    },
    vector<int>::IdxOutOfRange);
}


TEST(vector, exception_VectorEmptyErr) {
  EXPECT_THROW(
    {
      vector<int> v(10, 10);
      while (true) {
        v.pop_back();
      }
    },
    vector<int>::VectorEmptyErr);
}
