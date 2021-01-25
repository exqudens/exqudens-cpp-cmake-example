#include "exqudens/test/Runner.hpp"
#include "exqudens/test/Config.hpp"
#include "exqudens/util/StringUtilsTestSuite.hpp"
#include "exqudens/util/ImageUtilsTestSuite.hpp"
#include <string>

namespace exqudens::test {

  int Runner::run(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    Config::setExecutableFilePath(std::string(argv[0]));
    return RUN_ALL_TESTS();
  }

}
