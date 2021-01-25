#pragma once

#include <vector>
#include <array>
#include <string>

namespace exqudens::util {

  using Pixel  = std::array<unsigned char, 4>;
  using Row    = std::vector<Pixel>;
  using Image  = std::vector<Row>;
  using String = std::string;

  class ImageUtils {

    public:

      ImageUtils() = delete;

      static Image readPng(String path);

      ~ImageUtils() = delete;

  };

}
