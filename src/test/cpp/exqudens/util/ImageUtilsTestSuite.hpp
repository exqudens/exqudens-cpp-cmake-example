#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include "gtest/gtest.h"
#include "exqudens/test/Config.hpp"
#include "exqudens/util/ImageUtils.hpp"

namespace exqudens::example::test {

  using String     = std::string;
  using Path       = std::filesystem::path;
  using Config     = exqudens::test::Config;
  using ImageUtils = exqudens::util::ImageUtils;
  using Image      = exqudens::util::Image;
  using Pixel      = exqudens::util::Pixel;

  class ImageUtilsTestSuite : public testing::Test {

    public:

      static void SetUpTestSuite() {
        std::cout << "ImageUtilsTestSuite::SetUpTestSuite()" << std::endl;
      }

      static void TearDownTestSuite() {
        std::cout << "ImageUtilsTestSuite::TearDownTestSuite()" << std::endl;
      }

      static String toString(Pixel pixel) {
        String string = String("[")
            .append(std::to_string(pixel[0]))
            .append(", ")
            .append(std::to_string(pixel[1]))
            .append(", ")
            .append(std::to_string(pixel[2]))
            .append(", ")
            .append(std::to_string(pixel[3]))
            .append("]");
        return string;
      }

      ImageUtilsTestSuite() {
        std::cout << "ImageUtilsTestSuite()" << std::endl;
      }

      ~ImageUtilsTestSuite() override {
        std::cout << "~ImageUtilsTestSuite()" << std::endl;
      }

    protected:

      void SetUp() override {
        std::cout << "ImageUtilsTestSuite.SetUp()" << std::endl;
      }

      void TearDown() override {
        std::cout << "ImageUtilsTestSuite.TearDown()" << std::endl;
      }

  };

  TEST_F(ImageUtilsTestSuite, testReadPng1) {
    String path;
    Image image;
    int height;
    int width;
    int x;
    int y;
    String pixel;

    path = Path(Config::getExecutableDirPath())
        .append("..")
        .append("resources")
        .append("png")
        .append("census-transform-1.png")
        .string();
    image = ImageUtils::readPng(path);
    height = image.size();

    ASSERT_EQ(240, height) << "height: '" << height << "'";

    width = image[0].size();

    ASSERT_EQ(320, width) << "width: '" << width << "'";

    x = 0;
    y = 0;
    pixel = ImageUtilsTestSuite::toString(image[y][x]);

    ASSERT_EQ("[155, 164, 125, 255]", pixel) << "x/y: '" << x << "/" << y;

    x = 0;
    y = height - 1;
    pixel = ImageUtilsTestSuite::toString(image[y][x]);

    ASSERT_EQ("[219, 223, 154, 255]", pixel) << "x/y: '" << x << "/" << y;

    x = width - 1;
    y = height - 1;
    pixel = ImageUtilsTestSuite::toString(image[y][x]);

    ASSERT_EQ("[125, 125, 75, 255]", pixel) << "x/y: '" << x << "/" << y;

    x = width - 1;
    y = 0;
    pixel = ImageUtilsTestSuite::toString(image[y][x]);

    ASSERT_EQ("[255, 255, 226, 255]", pixel) << "x/y: '" << x << "/" << y;
  }

}
