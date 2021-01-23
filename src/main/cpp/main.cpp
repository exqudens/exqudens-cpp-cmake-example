#include "exqudens/util/StringUtils.hpp"

#include <string>
#include <cstdlib>
#include <filesystem>
#include <iostream>

using String      = std::string;
using Path        = std::filesystem::path;
using StringUtils = exqudens::util::StringUtils;

void parentPath() {
  if(const char* env_p = std::getenv("PATH")) {
    std::cout << "Your PATH is: '" << env_p << "'" << std::endl;
  }

  String string = "src/main";
  String expected = "main";

  std::cout << "processing path: '" << string << "'" << std::endl;

  String actual = Path(string.c_str()).parent_path().string();

  std::cout << "result: '" << actual << "'" << std::endl;

  if (expected != actual) {
    String message = "expected: '";
    message += expected;
    message += "' actual: '";
    message += actual;
    message += "'";
    std::cerr << message << std::endl;
  }
}

void trim() {
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
  }
}

int main(int argc, char** argv) {
  if (argc > 1) {

    String command = String(argv[1]);

    if ("--parent-path" == command) {
      parentPath();
    } else if ("--trim" == command) {
      trim();
    }

  }

  return 0;
}
