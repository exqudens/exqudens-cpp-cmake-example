#pragma once

#include <vector>
#include <array>
#include <string>

namespace exqudens::util {

  class ImageUtils {

    public:

      static std::vector<std::vector<std::array<char, 4>>> readPng(std::string path);

  };

}
