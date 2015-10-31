// Copyright Michael Park 2015
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <variant.hpp>

#include <string>

#include <gtest/gtest.h>

namespace exp = std::experimental;

using namespace std::string_literals;

TEST(Cnstr_Conversion, Direct) {
  exp::variant<int, std::string> v(42);
  EXPECT_EQ(42, exp::get<int>(v));

  /* constexpr */ {
    constexpr exp::variant<int, const char *> v(42);
    static_assert(42 == exp::get<int>(v), "");
  }
}

TEST(Cnstr_Conversion, DirectRef) {
  int expected = 42;
  exp::variant<int &, std::string &> v(expected);
  EXPECT_EQ(expected, exp::get<int &>(v));
  EXPECT_EQ(&expected, &exp::get<int &>(v));

  /* constexpr */ {
    static constexpr int expected = 42;
    constexpr exp::variant<const int &> v(expected);
    static_assert(expected == exp::get<const int &>(v), "");
    static_assert(&expected == &exp::get<const int &>(v), "");
  }
}

TEST(Cnstr_Conversion, DirectConversion) {
  exp::variant<int, std::string> v("42");
  EXPECT_EQ("42"s, exp::get<std::string>(v));

  /* constexpr */ {
    constexpr exp::variant<int, const char *> v(1.1);
    static_assert(1 == exp::get<int>(v), "");
  }
}

TEST(Cnstr_Conversion, DirectConversionRef) {
  std::ostringstream strm;
  exp::variant<int &, std::ostream &> v(strm);
  EXPECT_EQ(&strm, &exp::get<std::ostream &>(v));
}

TEST(Cnstr_Conversion, CopyInitialization) {
  exp::variant<int, std::string> v = 42;
  EXPECT_EQ(42, exp::get<int>(v));

  /* constexpr */ {
    constexpr exp::variant<int, const char *> v = 42;
    static_assert(42 == exp::get<int>(v), "");
  }
}

TEST(Cnstr_Conversion, CopyInitializationRef) {
  std::string expected = "42";
  exp::variant<int &, std::string &> v = expected;
  EXPECT_EQ(expected, exp::get<std::string &>(v));
  EXPECT_EQ(&expected, &exp::get<std::string &>(v));
}

TEST(Cnstr_Conversion, CopyInitializationConversion) {
  exp::variant<int, std::string> v = "42";
  EXPECT_EQ("42"s, exp::get<std::string>(v));

  /* constexpr */ {
    constexpr exp::variant<int, const char *> v = 1.1;
    static_assert(1 == exp::get<int>(v), "");
  }
}

TEST(Cnstr_Conversion, CopyInitializationConversionRef) {
  std::ostringstream strm;
  exp::variant<int &, std::ostream &> v = strm;
  EXPECT_EQ(&strm, &exp::get<std::ostream &>(v));
}
