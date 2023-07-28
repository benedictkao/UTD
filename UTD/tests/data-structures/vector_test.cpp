#include "gtest/gtest.h"

#include "../../src/data-structures/vector.h"

TEST(vector, constructors) {

  // Empty constructor
  utd::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.begin(), v.end());

  // size constructor
  utd::vector<int> v_size(10);
  EXPECT_EQ(v_size.size(), 10);
  EXPECT_NE(v_size.begin(), v_size.end());

  // size + val constructor
  utd::vector<int> v_size_val(11, 1);
  EXPECT_EQ(v_size_val.size(), 11);
  EXPECT_NE(v_size_val.begin(), v_size_val.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_size_val[i], 1);
  }
  EXPECT_EQ(*v_size_val.begin(), *v_size_val.end());

  // Copy constructor
  utd::vector<int> v_copy(v_size_val);
  EXPECT_EQ(v_copy.size(), 11);
  EXPECT_NE(v_copy.begin(), v_copy.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_copy[i], 1);
  }
  EXPECT_EQ(*v_copy.begin(), *v_copy.end());

  // Move constructor
  utd::vector<int> v_source(11, 100);
  utd::vector<int> v_move(std::move(v_source));
  EXPECT_EQ(v_source.size(), 0);
  EXPECT_EQ(v_move.size(), 11);
  EXPECT_NE(v_move.begin(), v_move.end());
  for (int i = 0; i < 11; i++) {
    EXPECT_EQ(v_move[i], 100);
  }
  EXPECT_EQ(*v_move.begin(), *v_move.end());
}

TEST(vector, methodsAndOperators) {
  utd::vector<int> v;
  size_t           v_size = 100;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.begin(), v.end());

  for (int i = 0; i < v_size; i++) {
    v.push_back(i);
  }

  EXPECT_EQ(v.size(), v_size);

  for (int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v.at(i), i);
    EXPECT_EQ(v[i], i);
    EXPECT_EQ(*(v.begin() + i), i);
  }

  int pop_back_times = 20;
  while (pop_back_times > 0) {
    v.pop_back();
    pop_back_times--;
    v_size--;
  }
  EXPECT_EQ(v.size(), v_size);
  for (int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v.at(i), i);
  }

  v.resize(10);
  EXPECT_EQ(v.size(), 10);
  for (int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v.at(i), i);
  }

  v.resize(20);
  EXPECT_EQ(v.size(), 20);
  for (int i = 0; i < v.size(); i++) {
    if (i < 10) {
      EXPECT_EQ(v.at(i), i);
    } else {
      EXPECT_EQ(v.at(i), 0);
    }
  }

  v.resize(30, 7);
  EXPECT_EQ(v.size(), 30);
  for (int i = 0; i < v.size(); i++) {
    if (i < 10) {
      EXPECT_EQ(v.at(i), i);
    } else if (i < 20) {
      EXPECT_EQ(v.at(i), 0);
    } else {
      EXPECT_EQ(v.at(i), 7);
    }
  }
}


TEST(vector, exceptions) {
  EXPECT_THROW(
    {
      utd::vector<int> v(10, 10);
      v[10];
    },

    utd::vector<int>::IdxOutOfRange);

  EXPECT_THROW(
    {
      utd::vector<int> v(10, 10);
      v.at(10);
    },
    utd::vector<int>::IdxOutOfRange);

  EXPECT_THROW(
    {
      utd::vector<int> v(10, 10);
      while (true) {
        v.pop_back();
      }
    },
    utd::vector<int>::VectorEmptyErr);
}
