#include "exqudens/util/ImageUtils.hpp"
#include "pngwriter.h"
#include <stdexcept>

namespace exqudens::util {

  using PNGWriter = pngwriter;

  Image ImageUtils::readPng(String path) {
    PNGWriter writer = PNGWriter(1, 1, 1, "");
    writer.readfromfile(path.c_str());
    int width = writer.getwidth();
    int height = writer.getheight();

    Image image(
        height,
        Row(
            width,
            {0, 0, 0, 0}
        )
    );

    for (int x = 1; x <= width; x++) {
      for (int y = 1; y <= height; y++) {

        bool hasColor = false;

        for (int color = 1; color <= 3; color++) {
          int intValue = writer.read(x, y, color) / 256;
          if (intValue > 255 || intValue < 0) {
            String message = String("x/y/color: '")
                .append(std::to_string(x))
                .append("/")
                .append(std::to_string(y))
                .append("/")
                .append(std::to_string(color))
                .append("': ")
                .append("intValue > 255 || intValue < 0");
            throw std::runtime_error(message);
          }
          unsigned char value = writer.read(x, y, color) / 256;
          image[y - 1][x - 1][color - 1] = value;
          if (!hasColor && value > 0) {
            hasColor = true;
          }
        }

        image[y - 1][x - 1][3] = hasColor ? 255 : 0;

      }
    }

    return image;
  }

}
