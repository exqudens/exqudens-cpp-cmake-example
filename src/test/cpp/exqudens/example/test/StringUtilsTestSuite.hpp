#ifndef EXQUDENS_EXAMPLE_STRING_UTILS_TEST_SUITE_HPP
#define EXQUDENS_EXAMPLE_STRING_UTILS_TEST_SUITE_HPP

#include <string>

#include "gtest/gtest.h"

#include "exqudens/example/StringUtils.hpp"

namespace exqudens::example::test {

  using String      = std::string;
  using StringUtils = exqudens::example::StringUtils;

  GTEST_TEST(StringUtilsTestSuite, test_1) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_EQ(expected, actual);
  }

  GTEST_TEST(StringUtilsTestSuite, test_2) {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb ccc";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    ASSERT_NE(expected, actual);
  }

}

#endif // EXQUDENS_EXAMPLE_STRING_UTILS_TEST_SUITE_HPP
