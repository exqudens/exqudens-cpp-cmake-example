#include "exqudens/test/Runner.hpp"
#include "exqudens/util/StringUtilsTestSuite.hpp"

namespace exqudens::test {

  int Runner::run(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

}
