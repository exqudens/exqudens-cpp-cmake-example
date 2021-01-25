#include <string>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include "exqudens/util/StringUtils.hpp"
#include "exqudens/util/ImageUtils.hpp"

using String      = std::string;
using Path        = std::filesystem::path;
using StringUtils = exqudens::util::StringUtils;
using ImageUtils  = exqudens::util::ImageUtils;
using Image       = exqudens::util::Image;

void parentPath() {
  if(const char* env_p = std::getenv("PATH")) {
    std::cout << "Your PATH is: '" << env_p << "'" << std::endl;
  }

  String string = "src/main";
  String expected = "src";

  std::cout << "processing path: '" << string << "'" << std::endl;

  String actual = Path(string.c_str()).parent_path().string();

  std::cout << "result: '" << actual << "'" << std::endl;

  if (expected != actual) {
    String message = "expected: '";
    message += expected;
    message += "' actual: '";
    message += actual;
    message += "'";
    throw std::runtime_error(message);
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
    throw std::runtime_error(message);
  }
}

void readPng(String executableFilePath) {
  std::filesystem::path filePath = std::filesystem::path(executableFilePath.c_str())
      .append("..")
      .append("..")
      .append("resources")
      .append("png")
      .append("census-transform-1.png");
  std::string filePathString = filePath.string();

  std::cout << "processing path: '" << filePathString << "'" << std::endl;

  Image image = ImageUtils::readPng(filePathString);
  int height = image.size();
  int width = image[0].size();
  String expected = "320/240";
  String actual = std::to_string(width).append("/").append(std::to_string(height));

  std::cout << "result: '" << actual << "'" << std::endl;

  if (expected != actual) {
    String message = "expected: '";
    message += expected;
    message += "' actual: '";
    message += actual;
    message += "'";
    throw std::runtime_error(message);
  }
}

int main(int argc, char** argv) {
  String executableFilePath = String(argv[0]);

  if (argc > 1) {

    String command = String(argv[1]);

    if ("--parent-path" == command) {
      parentPath();
    } else if ("--trim" == command) {
      trim();
    } else if ("--read-png" == command) {
      readPng(executableFilePath);
    }

  } else {
    parentPath();
    trim();
    readPng(executableFilePath);
  }

  return 0;
}
