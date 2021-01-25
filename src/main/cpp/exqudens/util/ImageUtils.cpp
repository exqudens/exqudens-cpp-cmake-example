#include "exqudens/util/ImageUtils.hpp"

#include "pngwriter.h"

namespace exqudens::util {

  using PNGWriter = pngwriter;

  std::vector<std::vector<std::array<char, 4>>> ImageUtils::readPng(std::string path) {
    PNGWriter writer = PNGWriter(1, 1, 1, "");
    writer.readfromfile(path.c_str());

    //writer.read(0, 0, 1);

    int width = writer.getwidth();
    int height = writer.getheight();
    std::vector<std::vector<std::array<char, 4>>> image(
        height,
        std::vector<std::array<char, 4>>(
            width,
            {0, 0, 0, 0}
        )
    );
    return image;
  }

}
