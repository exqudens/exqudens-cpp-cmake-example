#pragma once

#include <string>
#include "gtest/gtest.h"
#include "exqudens/util/StringUtils.hpp"

namespace exqudens::example::test {

  using String      = std::string;
  using StringUtils = exqudens::util::StringUtils;

  GTEST_TEST(StringUtilsTestSuite, test_1) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_EQ(expected, actual) << "Info: " << "my_test_info" << 1;
  }

  GTEST_TEST(StringUtilsTestSuite, test_2) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb ccc";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_NE(expected, actual) << "Info: " << "my_test_info" << 2;
  }

}
