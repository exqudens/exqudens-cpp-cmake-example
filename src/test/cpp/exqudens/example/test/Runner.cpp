#include "exqudens/example/test/Runner.hpp"
#include "exqudens/example/test/StringUtilsTestSuite.hpp"

namespace exqudens::example::test {

  int Runner::run(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

}
