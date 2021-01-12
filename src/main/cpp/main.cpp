#include "exqudens/util/StringUtils.hpp"

#include <string>
#include <iostream>

int main(int argc, char** argv) {
  using String      = std::string;
  using StringUtils = exqudens::util::StringUtils;

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
    std::cerr << message << std::endl;
    return 1;
  } else {
    return 0;
  }
}
