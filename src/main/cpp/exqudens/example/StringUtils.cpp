#include "exqudens/example/StringUtils.hpp"

namespace exqudens::example {

  const String StringUtils::WHITE_SPACES = " \n\r\t\f\v";

  String StringUtils::leftTrim(String string) {
    int start = string.find_first_not_of(WHITE_SPACES);
    return start == -1 ? "" : string.substr(start);
  }

  String StringUtils::rightTrim(String string) {
    int end = string.find_last_not_of(WHITE_SPACES);
    return end == -1 ? "" : string.substr(0, end + 1);
  }

  String StringUtils::trim(String string) {
    return leftTrim(rightTrim(string));
  }

}
