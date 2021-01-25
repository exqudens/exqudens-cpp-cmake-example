#pragma once

#include <string>
#include <iostream>
#include "gtest/gtest.h"
#include "exqudens/util/StringUtils.hpp"

namespace exqudens::example::test {

  using String      = std::string;
  using StringUtils = exqudens::util::StringUtils;

  class StringUtilsTestSuite : public testing::Test {

    public:

      static void SetUpTestSuite() {
        std::cout << "StringUtilsTestSuite::SetUpTestSuite()" << std::endl;
      }

      static void TearDownTestSuite() {
        std::cout << "StringUtilsTestSuite::TearDownTestSuite()" << std::endl;
      }

      StringUtilsTestSuite() {
        std::cout << "StringUtilsTestSuite()" << std::endl;
      }

      ~StringUtilsTestSuite() override {
        std::cout << "~StringUtilsTestSuite()" << std::endl;
      }

    protected:

      void SetUp() override {
        std::cout << "StringUtilsTestSuite.SetUp()" << std::endl;
      }

      void TearDown() override {
        std::cout << "StringUtilsTestSuite.TearDown()" << std::endl;
      }

  };

  TEST_F(StringUtilsTestSuite, test1) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_EQ(expected, actual) << "Info: " << "my_test_info" << 1;
  }

  TEST_F(StringUtilsTestSuite, test2) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb ccc";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_NE(expected, actual) << "Info: " << "my_test_info" << 2;
  }

}
