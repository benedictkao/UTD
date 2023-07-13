#include "gtest/gtest.h"

#include "../../src/data-structures/string32.h"

static const char* getDataAddress(const utd::string32& s) {
  return s.c_str();
}

static const char* getCapacityAddress(const utd::string32& s) {
  return ((char*) &s + 16);
}

static bool isSmallString(const utd::string32& s) {
  return getDataAddress(s) == getCapacityAddress(s);
}

TEST(string32, default_constructor) {
  utd::string32 s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.capacity(), 16);
  EXPECT_TRUE(s == "");
  EXPECT_TRUE(isSmallString(s));
  EXPECT_TRUE(isSmallString(s));
}

struct ConstructorArgs {
  const char* data;
  int         size;
  int         capacity;
};

class ConstructorTestFixture : public ::testing::TestWithParam<ConstructorArgs> {
protected:
  ConstructorArgs args;
};

TEST_P(ConstructorTestFixture, c_str_constructor) {
  auto          params = GetParam();
  utd::string32 s      = params.data;
  EXPECT_EQ(s.size(), params.size);
  EXPECT_EQ(s.capacity(), params.capacity);
  EXPECT_TRUE(s == params.data);
  EXPECT_EQ(isSmallString(s), s.size() <= 15);
}

TEST_P(ConstructorTestFixture, copy_constructor) {
  auto          params = GetParam();
  utd::string32 s      = params.data;
  utd::string32 s2(s);
  EXPECT_EQ(s2.size(), params.size);
  EXPECT_EQ(s2.capacity(), params.capacity);
  EXPECT_TRUE(s2 == params.data);
  EXPECT_EQ(isSmallString(s2), isSmallString(s));
}

TEST_P(ConstructorTestFixture, move_constructor) {
  auto          params = GetParam();
  utd::string32 s      = params.data;
  utd::string32 s2((utd::string32 &&) s);
  EXPECT_EQ(s2.size(), params.size);
  EXPECT_EQ(s2.capacity(), params.capacity);
  EXPECT_TRUE(s2 == params.data);
  EXPECT_EQ(isSmallString(s2), s2.size() <= 15);

  // Test moved string is in valid state
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.capacity(), 16);
  EXPECT_EQ(s.c_str(), nullptr);
}

INSTANTIATE_TEST_SUITE_P(
  string32,
  ConstructorTestFixture,
  ::testing::Values(ConstructorArgs{ "1234", 4, 16 },
                    ConstructorArgs{ "A heap allocated string.", 24, 25 }));

struct AssignmentArgs {
  const char* data1;
  const char* data2;
};

class AssignmentTestFixture : public ::testing::TestWithParam<AssignmentArgs> {
protected:
  AssignmentArgs args;
};

TEST_P(AssignmentTestFixture, copy_assignment) {
  auto          params = GetParam();
  utd::string32 s      = params.data1;
  utd::string32 s2     = params.data2;
  s                    = s2;
  EXPECT_EQ(s.size(), s2.size());
  EXPECT_EQ(s.capacity(), s2.capacity());
  EXPECT_TRUE(s == s2);
  EXPECT_EQ(isSmallString(s), isSmallString(s2));
}

TEST_P(AssignmentTestFixture, move_assignment) {
  auto          params = GetParam();
  utd::string32 s      = params.data1;
  utd::string32 s2     = params.data2;
  int           size   = s.size();
  int           capacity = s.capacity();
  bool          isSmall  = isSmallString(s);
  s2                    = (utd::string32 &&) s;
  EXPECT_EQ(s2.size(), size);
  EXPECT_EQ(s2.capacity(), capacity);
  EXPECT_TRUE(s2 == params.data1);
  EXPECT_EQ(isSmallString(s2), isSmall);

  // Test moved string is in valid state
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.capacity(), 16);
  EXPECT_EQ(s.c_str(), nullptr);
}

INSTANTIATE_TEST_SUITE_P(
  string32,
  AssignmentTestFixture,
  ::testing::Values(AssignmentArgs{ "12", "34567" },
                    AssignmentArgs{ "12", "A heap allocated string." },
                    AssignmentArgs{ "A heap allocated string.", "12" },
                    AssignmentArgs{ "A heap allocated string.",
                                    "Another heap allocated string." }));