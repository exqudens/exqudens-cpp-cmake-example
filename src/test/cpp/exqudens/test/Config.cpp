#include "exqudens/test/Config.hpp"
#include <filesystem>

namespace exqudens::test {

  std::string Config::executableFilePath = "";
  std::string Config::executableDirPath = "";

  void Config::setExecutableFilePath(std::string path) {
    executableFilePath = path;
    executableDirPath = std::filesystem::path(executableFilePath.c_str()).parent_path().string();
  }

  std::string Config::getExecutableFilePath() {
    return executableFilePath;
  }

  std::string Config::getExecutableDirPath() {
    return executableDirPath;
  }

}
