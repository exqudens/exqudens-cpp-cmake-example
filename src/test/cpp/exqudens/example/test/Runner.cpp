#include "exqudens/example/test/Runner.hpp"
#include "exqudens/example/test/StringUtilsTests.hpp"

#include <exception>
#include <stdexcept>
#include <iostream>

namespace exqudens::example::test {

  using Exception    = std::exception;
  using RuntimeError = std::runtime_error;

  // public

  int Runner::run(int argc, char** argv) {
    Vector<String> vector;
    for (int i = 1; i < argc; i++) {
      String string = String(argv[i]);
      vector.push_back(string);
    }
    return run(vector);
  }

  // private

  int Runner::run(Vector<String> vector) {
    try {
      Map<String, Test> testMap = createTestMap();
      for (const String& string : vector) {
        if (testMap.contains(string)) {
          Test test = testMap[string];
          test();
        } else {
          throw RuntimeError(String("test: '").append(string).append("' not found !!!"));
        }
      }
      return 0;
    } catch (Exception& e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }

  Map<String, Test> Runner::createTestMap() {
    Map<String, Test> testMap;

    testMap["StringUtilsTests.test_1"] = exqudens::example::test::StringUtilsTests::test_1;

    return testMap;
  }

}
