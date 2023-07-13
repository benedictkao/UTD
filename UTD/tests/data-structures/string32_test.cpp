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
  EXPECT_TRUE(s.empty());
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
  EXPECT_EQ(s.empty(), params.size == 0);
  EXPECT_EQ(s.capacity(), params.capacity);
  EXPECT_TRUE(s == params.data);
  EXPECT_EQ(isSmallString(s), s.size() <= 15);
}

TEST_P(ConstructorTestFixture, copy_constructor) {
  auto          params = GetParam();
  utd::string32 s      = params.data;
  utd::string32 s2(s);
  EXPECT_EQ(s2.size(), params.size);
  EXPECT_EQ(s2.empty(), params.size == 0);
  EXPECT_EQ(s2.capacity(), params.capacity);
  EXPECT_TRUE(s2 == params.data);
  EXPECT_EQ(isSmallString(s2), isSmallString(s));
}

TEST_P(ConstructorTestFixture, move_constructor) {
  auto          params = GetParam();
  utd::string32 s      = params.data;
  utd::string32 s2((utd::string32 &&) s);
  EXPECT_EQ(s2.size(), params.size);
  EXPECT_EQ(s2.empty(), params.size == 0);
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
  s2                    = s;
  EXPECT_EQ(s2.size(), s.size());
  EXPECT_EQ(s2.empty(), s.size() == 0);
  EXPECT_EQ(s2.capacity(), s.capacity());
  EXPECT_TRUE(s2 == s);
  EXPECT_EQ(isSmallString(s2), isSmallString(s));
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
  EXPECT_EQ(s2.empty(), size == 0);
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

struct ReserveArgs {
  const char* before;
  int         reserve;
  const char* after;
  int         capacity;
};

class ReserveTestFixture : public ::testing::TestWithParam<ReserveArgs> {
protected:
  ReserveArgs args;
};

TEST_P(ReserveTestFixture, reserve) {
  auto          params = GetParam();
  utd::string32 s      = params.before;
  s.reserve(params.reserve);
  EXPECT_TRUE(s == params.after);
  EXPECT_EQ(s.capacity(), params.capacity);
}

INSTANTIATE_TEST_SUITE_P(
  string32,
  ReserveTestFixture,
  ::testing::Values(
    ReserveArgs{ "123", 15, "123", 16 },
    ReserveArgs{ "A heap allocated string.",
                 15,
                 "A heap allocated string.",
                 25 },
    ReserveArgs{ "123", 20, "123", 21 },
    ReserveArgs{ "Heap allocated str", 20, "Heap allocated str", 21 },
    ReserveArgs{ "A heap allocated string.", 20, "A heap allocated str", 21 }));

TEST(string32, sq_bracket_operator) {
  utd::string32 s = "test";
  EXPECT_EQ(s[0], 't');
  EXPECT_EQ(s[2], 's');
  s[0] = 'T';
  EXPECT_TRUE(s == "Test");
}

struct StrConcatArgs {
  const char* init_str;
  const char* add_str_1;
  const char* str_res_1;
  const char* add_str_2;
  const char* str_res_2;
};

class StrConcatTestFixture : public ::testing::TestWithParam<StrConcatArgs> {
protected:
  StrConcatArgs args;
};

TEST_P(StrConcatTestFixture, str_concatentation) {
  auto          params = GetParam();
  utd::string32 s      = params.init_str;
  utd::string32 s2     = s + params.add_str_1;
  EXPECT_TRUE(s == params.init_str);
  EXPECT_TRUE(s2 == params.str_res_1);
  s2 += params.add_str_2;
  EXPECT_TRUE(s2 == params.str_res_2);
}

INSTANTIATE_TEST_SUITE_P(
  string32,
  StrConcatTestFixture,
  ::testing::Values(StrConcatArgs{ "12", "34", "1234", "56", "123456" },
                    StrConcatArgs{ "This is ",
                                   "a heap allocated string",
                                   "This is a heap allocated string",
                                   "!!",
                                   "This is a heap allocated string!!" },
                    StrConcatArgs{ "This is a heap all",
                                   "ocated",
                                   "This is a heap allocated",
                                   " string because it is long",
                                   "This is a heap allocated string because it is long" },
                    StrConcatArgs{ "This is a heap all",
                                   "ocated string",
                                   "This is a heap allocated string",
                                   "",
                                    "This is a heap allocated string" }));

struct CharConcatArgs {
  const char* init_str;
  char        add_char_1;
  const char* str_res_1;
  char        add_char_2;
  const char* str_res_2;
};

class CharConcatTestFixture : public ::testing::TestWithParam<CharConcatArgs> {
protected:
  CharConcatArgs args;
};

TEST_P(CharConcatTestFixture, char_concatentation) {
  auto          params = GetParam();
  utd::string32 s      = params.init_str;
  utd::string32 s2     = s + params.add_char_1;
  EXPECT_TRUE(s == params.init_str);
  EXPECT_TRUE(s2 == params.str_res_1);
  s2 += params.add_char_2;
  EXPECT_TRUE(s2 == params.str_res_2);
}

INSTANTIATE_TEST_SUITE_P(
  string32,
  CharConcatTestFixture,
  ::testing::Values(CharConcatArgs{ "12", '3', "123", '4', "1234" },
                    CharConcatArgs{ "A small string.", '.', "A small string..", '?', "A small string..?" },
                    CharConcatArgs{ "A small string",
                                    '.',
                                    "A small string.",
                                    '?',
                                    "A small string.?" },
                    CharConcatArgs{ "A heap allocated string",
                                    '?',
                                    "A heap allocated string?",
                                    '!',
                                    "A heap allocated string?!" }));