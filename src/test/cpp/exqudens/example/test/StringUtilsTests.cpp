#include "exqudens/example/test/StringUtilsTests.hpp"
#include "exqudens/example/StringUtils.hpp"

#include <iostream>
#include <stdexcept>

namespace exqudens::example::test {

  using RuntimeError = std::runtime_error;

  void StringUtilsTests::test_1() {
    String string = "\n aaa bbb\n   ";
    String expected = "aaa bbb";

    std::cout << "processing string: '" << string << "'" << std::endl;

    String actual = StringUtils::trim(string);

    std::cout << "result: '" << actual << "'" << std::endl;

    if (expected != actual) {
      String message = "expected: '";
      message += expected;
      message += "' actual: '";
      message += actual;
      message += "'";
      throw RuntimeError(message);
    }
  }

}
