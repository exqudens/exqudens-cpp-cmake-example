#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include "gtest/gtest.h"
#include "exqudens/test/Config.hpp"
#include "exqudens/util/ImageUtils.hpp"

namespace exqudens::example::test {

  using String       = std::string;
  using Path         = std::filesystem::path;
  using RunnerConfig = exqudens::test::Config;
  using ImageUtils   = exqudens::util::ImageUtils;

  class ImageUtilsTestSuite : public testing::Test {

    public:

      static void SetUpTestSuite() {
        std::cout << "ImageUtilsTestSuite::SetUpTestSuite()" << std::endl;
      }

      static void TearDownTestSuite() {
        std::cout << "ImageUtilsTestSuite::TearDownTestSuite()" << std::endl;
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

  TEST_F(ImageUtilsTestSuite, test1) {
    String path = Path(RunnerConfig::getExecutableDirPath())
        .append("..")
        .append("resources")
        .append("png")
        .append("census-transform-1.png")
        .string();
    std::vector<std::vector<std::array<char, 4>>> image = ImageUtils::readPng(path);

    std::cout << "width: " << image[0].size() << std::endl;
    std::cout << "height: " << image.size() << std::endl;
  }

}
