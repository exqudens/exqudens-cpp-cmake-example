#pragma once

#include <string>

namespace exqudens::test {

  class Config {

    friend class Runner;

    private:

      static std::string executableFilePath;
      static std::string executableDirPath;

      static void setExecutableFilePath(std::string path);

    public:

      static std::string getExecutableFilePath();
      static std::string getExecutableDirPath();

  };

}
