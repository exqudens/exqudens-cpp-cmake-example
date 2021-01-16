#include "exqudens/util/StringUtils.hpp"

#include <string>
#include <cstdlib>
#include <filesystem>
#include <iostream>

using String      = std::string;
using Path        = std::filesystem::path;
using StringUtils = exqudens::util::StringUtils;

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

void parentPath(String string) {
  if(const char* env_p = std::getenv("PATH")) {
    std::cout << "Your PATH is: '" << env_p << "'" << std::endl;
  }
  String s = Path(string.c_str()).parent_path().string();
  std::cout << "Parent PATH is: '" << s << "'" << std::endl;
}

int main(int argc, char** argv) {
  if (argc > 1) {

    String command = String(argv[1]);

    if ("--trim" == command) {
      trim();
    } else if ("--parent-path" == command) {
      parentPath(String(argv[2]));
    }

  }

  return 0;
}
